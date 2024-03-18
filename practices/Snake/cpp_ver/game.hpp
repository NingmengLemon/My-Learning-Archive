#ifndef _GAME_HPP_
#define _GAME_HPP_

#include "./Eseq/eseq.hpp"
#include <iostream>
#include <random>
#include <unordered_map>
#include <map>
#include <vector>
#include <sstream>

const std::string EMPTY_REPR = "  ";
const std::string SNAKE_REPR = "[]";
const std::string FOODA_REPR = "()";
const std::string FOODB_REPR = "<>";
const std::string FOODC_REPR = "{}";
const std::string BRICK_REPR = "##";


struct Coor {
    Coor(void);
    Coor(int x, int y);
    int x;
    int y;
    bool operator==(const Coor &other) const;
    void change(int x = 0, int y = 0);
    void change(Coor c);
    Coor(const Coor &other);
};

namespace std {
template <> struct hash<Coor>;
}

enum Direction { UP, DOWN, LEFT, RIGHT };
const std::vector<Direction> DIRECTIONS = {UP, DOWN, LEFT, RIGHT};

// enum Operation {};

enum ObjectType { SNAKE, BRICK, FOODA, FOODB, FOODC, EMPTY };

class GameObj {
  public:
    GameObj(void);
    GameObj(int x, int y, ObjectType type, std::string repr, int healta);
    GameObj(Coor c, ObjectType type, std::string repr, int healta);
    void moveTo(int x, int y);
    void moveTo(Coor c);
    std::string getRepr(void);
    int getHealta(void);
    ObjectType getType(void);
    Coor getCoor(void);
    // void changeRepr(std::string new_repr);

    GameObj(const GameObj &other);

  private:
    Coor coor;
    ObjectType type;
    std::string repr;
    int healta;
};

class Game {
  public:
    Game(int w = 20, int h = 20);
    void start(void);
    void operate(char key);
    void nextFrame(void);
    std::string render(void);
    // 设置, 但是大部分需要一开始就设置
    bool dieIfCrashSelf = false; //
    bool summonMoreKindOfFood = true; //
    bool summonMoreFood = true; //
    int healthReducedByWall = -9999; //
    bool generateBoundryWall = true; //
    bool summonMoreWall = false; //
    bool colorful = true; //
    int initLength = 1; //
    // 因为延时由外部驱动决定, 所以速度设置不在这里
    // 数据获取接口
    Coor getHeadCoor(void);
    int getWidth(void);
    int getHeight(void);
    int getLength(void);
    Direction getDirection(void);

  private:
    // 除蛇蛇外的其他游戏对象
    std::vector<GameObj> gameobjs;
    // 游戏操作
    void summonBoundary(int wall_healta = -999); // 生成地图边界墙
    std::vector<Coor> getEmptyGrids(void);       // 找出空的坐标们
    void placeNewFood(bool isInit = false);
    GameObj getFood(Coor c, bool allowRandom = false);
    void placeNewWall(unsigned int amount);
    // 根据坐标和方向得到下一刻所在的坐标
    static Coor calcNextPos(Coor c, Direction d);
    // 地图参数
    int width;
    int height;
    // 蛇蛇属性
    std::vector<GameObj> snake;
    Direction direction;
    int folded = 0;
    // 随机数操作
    int getRandom(int a, int b); // 生成随机数
    std::mt19937 gen;
    // 着色
    static std::string color(ObjectType type, std::string s);
};

class GameOver : public std::exception {
  private:
    std::string message;

  public:
    GameOver(const std::string &msg);
    const char *what() const noexcept override;
};

#endif