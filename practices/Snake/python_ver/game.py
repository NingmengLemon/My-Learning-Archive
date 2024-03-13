import os
import random
import time

import keyboard


UP = 1
DOWN = 2
LEFT = 3
RIGHT = 4
DIRECTIONS = [UP, DOWN, LEFT, RIGHT]

DIRECTION_KEY_MAP = {
    "left": LEFT,
    "up": UP,
    "right": RIGHT,
    "down": DOWN,
    "w": UP,
    "s": DOWN,
    "a": LEFT,
    "d": RIGHT,
}

EMPTY_CHAR = "  "
SNAKE_CHAR = "[]"
FOOD_CHAR = "()"
BRICK_CHAR = "##"


class GameObj:
    def __init__(self, x, y, health_delta=0) -> None:
        self.x, self.y = x, y
        self.collide_health_delta = health_delta

    @property
    def coor(self):
        return self.x, self.y

    def __str__(self):
        return EMPTY_CHAR


class SnakeBody(GameObj):
    def __init__(self, x, y) -> None:
        super().__init__(x, y, health_delta=0)

    def __str__(self) -> str:
        return SNAKE_CHAR


class Brick(GameObj):
    def __init__(self, x, y) -> None:
        super().__init__(x, y, health_delta=-999)

    def __str__(self) -> str:
        return BRICK_CHAR


class Food(GameObj):
    def __init__(self, x, y) -> None:
        super().__init__(x, y, health_delta=1)

    def __str__(self) -> str:
        return FOOD_CHAR


class GameOver(Exception):
    pass


class Game:
    def __init__(self, w, h) -> None:
        self.width, self.height = w, h

        self.snake: list[SnakeBody] = [SnakeBody(round(w / 2), round(h / 2))]
        self.snake_direction = random.choice(DIRECTIONS)
        self.snake_not_stretched = 0
        # self.brick: list[Brick] = []
        # self.foods: list[Food] = []
        self.gameobjs: list[Brick, Food] = []
        for y in range(self.height):
            for x in range(self.width):
                if x == w - 1 or x == 0 or y == h - 1 or y == 0:
                    self.gameobjs += [Brick(x, y)]

        self.update_query_dict()
        self.place_new_food()

    def update_query_dict(self):
        self.query = {i.coor: i for i in self.snake + self.gameobjs}

    def render(self):
        frame = ""
        # self.brick + self.foods}
        for y in range(self.height):
            for x in range(self.width):
                if obj := self.query.get((x, y), None):
                    frame += str(obj)
                else:
                    frame += EMPTY_CHAR
            frame += "\n"
        frame += "Length: %d" % len(self.snake)
        return frame

    @property
    def all_coors(self):
        w, h = self.width, self.height
        r = set()
        for y in range(h):
            for x in range(w):
                r.add((x, y))
        return r

    def next_frame(self):
        self.update_query_dict()
        query_before = self.query

        snake_head_next_xy = tuple(
            [
                sum(i)
                for i in zip(
                    self.snake[0].coor, Game.direction_to_motion(self.snake_direction)
                )
            ]
        )

        if collided_obj := query_before.get(snake_head_next_xy, None):
            collided_obj: GameObj
            if len(self.snake) + collided_obj.collide_health_delta < 1:
                raise GameOver
            if isinstance(collided_obj, SnakeBody):
                self.snake = self.snake[: self.snake.index(collided_obj)]
            else:
                self.gameobjs.remove(collided_obj)
                if (hd := collided_obj.collide_health_delta) > 0:
                    self.snake_not_stretched += hd
                else:
                    self.snake = self.snake[:hd]

            self.update_query_dict()
            if isinstance(collided_obj, Food):
                self.place_new_food()

        self.snake = [SnakeBody(*snake_head_next_xy)] + self.snake
        if self.snake_not_stretched > 0:
            self.snake_not_stretched -= 1
        else:
            self.snake.pop(-1)

    @property
    def free_spaces(self):
        return [c for c in list(self.all_coors.difference(set(self.query.keys())))]

    def place_new_food(self):
        self.gameobjs.append(Food(*random.choice(self.free_spaces)))

    @staticmethod
    def direction_to_motion(d):
        x_motion = {RIGHT: 1, LEFT: -1}[d] if d in [RIGHT, LEFT] else 0
        y_motion = {UP: -1, DOWN: 1}[d] if d in [UP, DOWN] else 0
        return x_motion, y_motion

    def operate(self, key):
        if key in DIRECTION_KEY_MAP:
            d = DIRECTION_KEY_MAP[key]
            nx, ny = Game.direction_to_motion(d)
            bx, by = Game.direction_to_motion(self.snake_direction)
            if nx != -bx and ny != -by:
                self.snake_direction = d


def main():
    game = Game(60, 30)
    keyboard.on_press(lambda event: game.operate(event.name))
    while True:
        print(game.render())
        time.sleep(0.15)
        os.system("cls")
        game.next_frame()


if __name__ == "__main__":
    main()
