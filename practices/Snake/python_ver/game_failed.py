import keyboard
import time
import os
import random


SNAKE_HEAD = "@"
SNAKE_BODY = "o"
BRICK = "#"
FOOD_A = "$"
FOOD_B = "%"


class GameObj(object):
    def __init__(self, x: int, y: int, type_: str) -> None:
        self.x, self.y = x, y
        self.type = type_

    def get_coor(self):
        return self.x, self.y

    def move(self, x, y):
        self.x, self.y = x, y


UP = 0
DOWN = 1
LEFT = 2
RIGHT = 3
DIRECTIONS = [UP, DOWN, LEFT, RIGHT]


class GameOver(Exception):
    pass


class Stage(object):
    def __init__(self, w: int = 60, h: int = 60) -> None:
        self.width, self.height = w, h
        self.objs: list[GameObj] = []
        self.snake = Snake(round(w/2), round(h/2), UP)
        for y in range(self.height):
            for x in range(self.width):
                if x==w-1 or x==0 or y==h-1 or y==0:
                    self.objs += [GameObj(x, y, BRICK)]

    def add_obj(self, x, y, type_):
        self.objs += [GameObj(x, y, type_)]

    def render(self):
        objs = {
            i.get_coor(): i.type
            for i in self.objs + self.snake.bodies + [self.snake.head]
        }
        s = ""
        for y in range(self.height):
            for x in range(self.width):
                s += objs.get((x, y), " ")
            s += "\n"
        s += 'Length: %d; Body to Stretch: %d'%(len(self.snake.bodies)+1, self.snake.not_stretched)
        return s
    
    @staticmethod
    def direction_to_motion(d):
        x_motion = {RIGHT: 1, LEFT: -1}[d] if d in [RIGHT, LEFT] else 0
        y_motion = {UP: -1, DOWN: 1}[d] if d in [UP, DOWN] else 0
        return x_motion,y_motion

    def next_frame(self):
        d = self.snake.direction
        # .---------------------------> x
        # |
        # |
        # |
        # |
        # |
        # |
        # v y
        
        x_motion,y_motion = Stage.direction_to_motion(d)
        head_next_coor = (self.snake.head.x + x_motion, self.snake.head.x + y_motion)
        objs_with_hd = {
            (i.x, i.y): i.type for i in self.objs
        }  # coor: health_delta
        health = len(self.snake.bodies) + 1
        # 碰撞判定
        cobj = objs_with_hd.get(head_next_coor, -1)
        if cobj != -1:
            health_delta = Stage.calc_health_delta(cobj)
            health += health_delta
            if health <= 0:
                raise GameOver
        # 移除物块
        if cobj in [FOOD_A, FOOD_B]:
            self.objs.remove(cobj)
        # 移动
        if cobj == -1:
            self.snake.move((x_motion, y_motion))
        else:
            self.snake.move((x_motion, y_motion), health_delta)
        # 新食物
            if health_delta > 0:
                self.place_new_food()

    @staticmethod
    def calc_health_delta(type_):
        if type_ in [SNAKE_HEAD, SNAKE_BODY, BRICK]:
            return -9999
        elif type_ == FOOD_A:
            return 1
        elif type_ == FOOD_B:
            return 2

    @staticmethod
    def key_to_direction(key):
        match key:
            case "up" | "w":
                return UP
            case "down" | "s":
                return DOWN
            case "left" | "a":
                return LEFT
            case "right" | "d":
                return RIGHT
            case _:
                return -1
            
    @staticmethod
    def get_all_coors(w, h):
        r = set()
        for y in range(h):
            for x in range(w):
                r.add((x,y))
        return r
    
    def place_new_food(self):
        type_ = random.choice([FOOD_A, FOOD_B])
        free_spaces = Stage.get_all_coors(self.width,self.height).difference({(i.x,i.y) for i in self.objs + self.snake.bodies + [self.snake.head]})
        self.objs += [GameObj(*random.choice(list(free_spaces)), type_)]

class Snake(object):
    def __init__(self, x: int, y: int, d: int) -> None:
        self.direction = d
        self.x, self.y = x, y
        self.head = GameObj(x, y, SNAKE_HEAD)
        self.bodies: list[GameObj] = [GameObj(*(0-i for i in Stage.direction_to_motion(d)), SNAKE_BODY)]
        self.not_stretched = 10

    def move(self, motion: tuple[int, int], lengthen: int = 0):
        self.not_stretched += lengthen

        vx, vy = motion
        lx, ly = last_xy = self.head.get_coor()
        new_xy = vx + lx, vy + ly
        self.head.move(*new_xy)

        for i in range(len(self.bodies)):
            self.bodies[i].move(*last_xy)
            last_xy = self.bodies[i].get_coor()
        if self.not_stretched:
            self.not_stretched -= 1
            self.bodies += [GameObj(*last_xy, SNAKE_BODY)]

    def turn(self, d):
        if d in DIRECTIONS and d != self.direction:
            nx,ny = Stage.direction_to_motion(d)
            bx,by = Stage.direction_to_motion(self.direction)
            if nx!=-bx and ny!=-by:
                self.direction = d


def main():
    game = Stage(60, 60)
    keyboard.on_press(lambda event: game.snake.turn(game.key_to_direction(event.name)))
    game.place_new_food()
    while True:
        print(game.render())
        time.sleep(0.1)
        os.system("cls")
        game.next_frame()


if __name__ == "__main__":
    main()
