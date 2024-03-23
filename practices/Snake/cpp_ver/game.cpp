#include "game.hpp"

Coor::Coor(int x, int y) : x(x), y(y) {}
Coor::Coor(void) : x(0), y(0) {}
Coor::Coor(const Coor &other) {
    x = other.x;
    y = other.y;
}
bool Coor::operator==(const Coor &other) const {
    return x == other.x && y == other.y;
}
void Coor::change(int new_x, int new_y) {
    x = new_x;
    y = new_y;
}
void Coor::change(Coor c) {
    x = c.x;
    y = c.y;
}
// 坐标对象的哈希支持
namespace std {
template <> struct hash<Coor> {
    std::size_t operator()(const Coor &obj) const {
        std::size_t hash_x = std::hash<int>()(obj.x);
        std::size_t hash_y = std::hash<int>()(obj.y);
        return hash_x * 31 + hash_y;
    }
};
} // namespace std

GameObj::GameObj(void) {
    coor = Coor(0, 0);
    type = EMPTY;
    repr = EMPTY_REPR;
    healta = 0;
}
GameObj::GameObj(const GameObj &other) {
    coor = other.coor;
    type = other.type;
    repr = other.repr;
    healta = other.healta;
}
GameObj::GameObj(int x, int y, ObjectType type, std::string repr, int healta)
    : coor(x, y), type(type), repr(repr), healta(healta) {}
GameObj::GameObj(Coor c, ObjectType type, std::string repr, int healta)
    : coor(c), type(type), repr(repr), healta(healta) {}
void GameObj::moveTo(int x, int y) { coor.change(x, y); }
void GameObj::moveTo(Coor c) { coor.change(c); }
std::string GameObj::getRepr(void) { return repr; }
int GameObj::getHealta(void) { return healta; }
ObjectType GameObj::getType(void) { return type; }
Coor GameObj::getCoor(void) { return Coor(coor); }

Game::Game(int w, int h) {
    std::random_device rd;
    gen = std::mt19937(rd());

    width = w;
    height = h;
    direction = DIRECTIONS.at(getRandom(0, DIRECTIONS.size() - 1));
}

bool Game::isAlive(void) { return alive; }
std::string Game::getCauseOfDeath(void) { return causeOfDeath; }

void Game::start(void) {
    if (initLength == 0) {
        alive = false;
        causeOfDeath = "initial length = 0";
        return;
    }
    folded = initLength - 1;
    snake.push_back(GameObj(width / 2, height / 2, SNAKE, SNAKE_REPR, 0));
    // 生成边界墙
    if (generateBoundryWall) {
        summonBoundary(healthReducedByWall);
    }
    // 放置食物
    placeNewFood(true);
    // 随机生成墙
    if (summonMoreWall) {
        placeNewWall(getRandom(1, 10));
    }
}

void Game::placeNewWall(unsigned int amount) {
    if (!amount)
        return;
    auto grids = getEmptyGrids();
    if (grids.empty())
        return;
    else {
        auto coor = grids.at(getRandom(0, grids.size() - 1));
        // 有概率刷出异格(?)食物, 但初始化时一定会刷出正面食物
        gameobjs.push_back(
            GameObj(coor, BRICK, BRICK_REPR, healthReducedByWall));
    }
    placeNewWall(amount - 1);
}

int Game::getRandom(int a, int b) {
    std::uniform_int_distribution<> distrib(a, b);
    return distrib(gen);
}

void Game::summonBoundary(int wall_healta) {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (x == 0 || x == width - 1 || y == 0 || y == height - 1) {
                gameobjs.push_back(
                    GameObj(x, y, BRICK, BRICK_REPR, wall_healta));
            }
        }
    }
}

Coor Game::calcNextPos(Coor c, Direction d) {
    Coor new_coor = Coor(c);
    switch (d) {
    case UP:
        new_coor.y -= 1;
        break;
    case DOWN:
        new_coor.y += 1;
        break;
    case LEFT:
        new_coor.x -= 1;
        break;
    case RIGHT:
        new_coor.x += 1;
        break;
    }
    return new_coor;
}

void Game::nextFrame(void) {
    if (!alive)
        return;
    Coor head_next_coor = calcNextPos(snake.front().getCoor(), direction);
    // 地图越界检查
    if (head_next_coor.x > width - 1)
        head_next_coor.x = 0;
    else if (head_next_coor.x < 0)
        head_next_coor.x = width - 1;
    else if (head_next_coor.y < 0)
        head_next_coor.y = height - 1;
    else if (head_next_coor.y > height - 1)
        head_next_coor.y = 0;
    // 检查与其他对象的碰撞
    bool place_new_flag = false;
    for (auto obj = gameobjs.begin(); obj != gameobjs.end();) {
        if (head_next_coor == obj->getCoor()) {
            // 判定死亡
            int healta = obj->getHealta();
            // int after_health = snake.size() + healta;
            if (((int)snake.size() + healta) < 1) {
                alive = false;
                causeOfDeath = "crash into something...";
                return;
            } else {
                if (healta > 0) {
                    folded += healta;
                } else if (healta < 0) {
                    while (healta < 0) {
                        snake.pop_back();
                        healta += 1;
                    }
                }
                obj = gameobjs.erase(obj);
                place_new_flag = true;
                continue;
            }
        }
        obj++;
    }
    if (place_new_flag) {
        placeNewFood();
    }
    // 检查与自身的碰撞
    int index = 0;
    bool crash_flag = false;
    for (GameObj obj : snake) {
        if (head_next_coor == obj.getCoor()) {
            // 根据设置判定是断尾还是死亡
            if (dieIfCrashSelf) {
                alive = false;
                causeOfDeath = "crash into self";
                return;
            } else {
                crash_flag = true;
                break;
            }
        }
        index += 1;
    }
    // 截断
    if (crash_flag) {
        int length_to_cut = snake.size() - index - 1;
        for (int i = 0; i < length_to_cut; i++)
            snake.pop_back();
    }
    // 收尾工作
    snake.insert(snake.begin(), GameObj(head_next_coor, SNAKE, SNAKE_REPR, 0));
    if (folded) {
        folded -= 1;
    } else {
        snake.pop_back();
    }
}

std::string Game::render(void) {
    std::string result = "";
    std::unordered_map<Coor, GameObj> temp_map;
    for (GameObj obj : gameobjs) {
        temp_map[obj.getCoor()] = obj;
    }
    for (GameObj obj : snake) {
        temp_map[obj.getCoor()] = obj;
    }
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            Coor c = Coor(x, y);
            auto search = temp_map.find(c);
            if (search != temp_map.end()) {
                auto obj = temp_map[c];
                auto repr = obj.getRepr();
                if (colorful)
                    repr = Game::color(obj.getType(), repr);
                result += repr;
            } else {
                result += EMPTY_REPR;
            }
        }
        result += "\n";
    }

    return result;
}

std::string Game::color(ObjectType type, std::string s) { // color (动词)
    switch (type) {
    case FOODA:
        return eseq::style::SetForeColor(eseq::style::colors::fore::GREEN) + s +
               eseq::style::ResetStyle();
    case FOODB:
        return eseq::style::SetForeColor(eseq::style::colors::fore::YELLOW) +
               s + eseq::style::ResetStyle();
    case FOODC:
        return eseq::style::SetForeColor(eseq::style::colors::fore::RED) + s +
               eseq::style::ResetStyle();
    case BRICK:
        return eseq::style::SetForeColor(eseq::style::colors::fore::GRAY) + s +
               eseq::style::ResetStyle();
    default:
        return s;
    }
}

Coor Game::getHeadCoor(void) { return Coor(snake.front().getCoor()); }
int Game::getWidth(void) { return width; }
int Game::getHeight(void) { return height; }
int Game::getLength(void) { return snake.size(); }
Direction Game::getDirection(void) { return direction; }

void Game::operate(char key) {
    switch (key) {
    case 'W':
    case 'w':
    // case 72:
        if (direction != DOWN) {
            direction = UP;
        }
        break;
    case 'S':
    case 's':
    // case 80:
        if (direction != UP) {
            direction = DOWN;
        }
        break;
    case 'A':
    case 'a':
    // case 75:
        if (direction != RIGHT) {
            direction = LEFT;
        }
        break;
    case 'D':
    case 'd':
    // case 77:
        if (direction != LEFT) {
            direction = RIGHT;
        }
        break;
    }
}

std::vector<Coor> Game::getEmptyGrids(void) {
    std::vector<std::vector<bool>> stage(height, std::vector<bool>(width, false));
    std::vector<Coor> result;
    for (GameObj obj : snake) {
        Coor c = obj.getCoor();
        stage[c.y][c.x] = true;
    }
    for (GameObj obj : gameobjs) {
        Coor c = obj.getCoor();
        stage[c.y][c.x] = true;
    }
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (!stage[y][x]) {
                result.push_back(Coor(x, y));
            }
        }
    }
    return result;
}

void Game::placeNewFood(bool isInit) {
    auto grids = getEmptyGrids();
    if (grids.empty())
        return;
    else {
        auto coor = grids.at(getRandom(0, grids.size() - 1));
        // 有概率刷出异格(?)食物, 但初始化时一定会刷出正面食物
        gameobjs.push_back(getFood(coor, summonMoreKindOfFood && !isInit));
    }
    if (!summonMoreFood)
        return;
    // 有概率多刷几个食物
    std::vector<bool> samples = {0, 0, 0, 0, 0, 0, 0, 1}; // 12.5%
    if (samples.at(getRandom(0, samples.size() - 1))) {
        placeNewFood();
    }
}

GameObj Game::getFood(Coor c, bool allowRandom) {
    if (allowRandom) {
        std::vector<int> samples = {0, 0, 0, 0, 0, 0, 0, 1, 1, 2};
        int type = samples.at(getRandom(0, samples.size() - 1));
        switch (type) {
        case 1:
            return GameObj(c, FOODB, FOODB_REPR, 2);
        case 2:
            return GameObj(c, FOODC, FOODC_REPR, -1);
        default:
            break;
        }
    }
    return GameObj(c, FOODA, FOODA_REPR, 1);
}