import random
import copy

UP = "w"
DOWN = "s"
LEFT = "a"
RIGHT = "d"
AVAILABLE_OPERATIONS = [UP, DOWN, LEFT, RIGHT]


class _2048Obj(object):
    def __init__(self, size: int = 4, iter_limit: int = 20) -> None:
        # max: 2**iter_limit, -1 means inf.
        # size: x*x matrix stage
        self.size = size
        self.unit_width = len(str(2**iter_limit)) if iter_limit > 0 else -1
        self.iter_limit = iter_limit if iter_limit > 1 else -1
        self.content = []
        for i in range(size):
            self.content += [[0] * size]
        self._fill_empty(2)
        self._fill_empty(4)

    def print(self) -> None:
        width = self.unit_width if self.unit_width != -1 else self._get_max_width()
        for y in range(self.size):
            print("-" * (self.size * (width + 1) + 1))
            for x in range(self.size):
                print("|", end="")
                print("%*d" % (width, self.content[y][x]), end="")
            print("|")
        print("-" * (self.size * (width + 1) + 1))

    def _get_max(self) -> int:
        res = 0
        for y in range(self.size):
            for x in range(self.size):
                var = self.content[y][x]
                if var >= res:
                    res = var
        return res

    def _get_max_width(self) -> int:
        return len(str(self._get_max()))

    def _get_all_empty(self) -> list:
        res = []
        for y in range(self.size):
            for x in range(self.size):
                var = self.content[y][x]
                if var == 0:
                    res.append((x, y))
        return res

    def _check_if_limit_reached(self) -> bool:
        if self.iter_limit == -1:
            return False
        limit = 2**self.iter_limit
        return self._get_max() >= limit

    def _check_if_end(self) -> bool:
        if self._check_if_limit_reached():
            return True
        for y in range(self.size):
            for x in range(self.size):
                if self.content[y][x] == 0:
                    return False
                if x < self.size-1:
                    if self.content[y][x + 1]==self.content[y][x]:
                        return False
                if y < self.size-1:
                    if self.content[y + 1][x]==self.content[y][x]:
                        return False
        return True

    def _fill_empty(self, num=2) -> tuple:
        empty = self._get_all_empty()
        if empty:
            x, y = random.choice(empty)
            self.content[y][x] = num
            return x, y
        else:
            return None

    def _merge_single(self, line: list) -> list:
        # from end to first
        flag = True
        while flag:
            flag = False
            for x in range(1, len(line)):
                if (not line[x - 1]) and line[x]:
                    line[x - 1] = line[x]
                    line[x] = 0
                    flag = True
                if line[x - 1] == line[x] and line[x] != 0:
                    line[x - 1] = line[x] * 2
                    line[x] = 0
                    flag = True
        return line

    def _merge(self, orient: str):
        if orient in [UP, DOWN]:
            for x in range(self.size):
                column = [line[x] for line in self.content]
                if orient == DOWN:
                    column.reverse()
                column = self._merge_single(column)
                if orient == DOWN:
                    column.reverse()
                for y in range(self.size):
                    self.content[y][x] = column[y]
        elif orient in [LEFT, RIGHT]:
            for y in range(self.size):
                line = self.content[y]
                if orient == RIGHT:
                    line.reverse()
                line = self._merge_single(line)
                if orient == RIGHT:
                    line.reverse()
                self.content[y] = line

    def _check_common(self, sheet: list) -> bool:
        return sheet == self.content

    def _operate(self, orient: str) -> None:
        c = copy.deepcopy(self.content)
        self._merge(orient=orient)
        if not self._check_common(c):
            self._fill_empty()

    def play(self) -> None:
        d = {UP: "↑", DOWN: "↓", LEFT: "←", RIGHT: "→"}
        c.print()
        o = ""
        while not self._check_if_end():
            if not o:
                o = input("Operate:").lower()
            while o:
                if o[-1] in AVAILABLE_OPERATIONS:
                    self._operate(o[-1])
                    print(d[o[-1]], end="")
                o = o[:-1]
            print("")
            self.print()
        print("GAME OVER!")


if __name__ == "__main__":
    c = _2048Obj(size=4, iter_limit=-1)
    c.play()
