#include "./ui.hpp"

void printStatus(Game &game, int delay) {
    const int gap = 3;
    // 相关信息
    std::cout << eseq::cursor::MoveTo(1, game.getWidth() * 2 + gap)
              << "        Length: "
              << eseq::style::SetForeColor(eseq::style::colors::fore::BLUE)
              << game.getLength() << eseq::style::ResetStyle();
    std::cout << eseq::cursor::MoveTo(3, game.getWidth() * 2 + gap)
              << "Head direction: ";
    switch (game.getDirection()) {
    case UP:
        std::cout << "↑";
        break;
    case DOWN:
        std::cout << "↓";
        break;
    case LEFT:
        std::cout << "←";
        break;
    case RIGHT:
        std::cout << "→";
        break;
    default:
        break;
    }
    Coor c = game.getHeadCoor();
    std::cout << eseq::cursor::MoveTo(5, game.getWidth() * 2 + gap)
              << " Head position: (" << c.x << ", " << c.y << ")   ";
    std::cout << eseq::cursor::MoveTo(7, game.getWidth() * 2 + gap)
              << "    Stage size: " << game.getWidth() << " x "
              << game.getHeight();
    std::cout << eseq::cursor::MoveTo(9, game.getWidth() * 2 + gap)
              << " Current speed: "
              << eseq::style::SetForeColor(eseq::style::colors::fore::BLUE)
              << 1 * 1000 * 1000 / delay << eseq::style::ResetStyle()
              << " grid/s";
}
void printTips(Game &game) {
    const int gap = 3;
    // Tips
    std::cout << eseq::cursor::MoveTo(11, game.getWidth() * 2 + gap) << "Use "
              << eseq::style::SetForeColor(eseq::style::colors::fore::BLUE)
              << "WASD" << eseq::style::ResetStyle() << " to turn";
    std::cout << eseq::cursor::MoveTo(12, game.getWidth() * 2 + gap) << "Use "
              << eseq::style::SetForeColor(eseq::style::colors::fore::BLUE)
              << "Q" << eseq::style::ResetStyle() << "(-), "
              << eseq::style::SetForeColor(eseq::style::colors::fore::BLUE)
              << "E" << eseq::style::ResetStyle() << "(+) and "
              << eseq::style::SetForeColor(eseq::style::colors::fore::BLUE)
              << "R" << eseq::style::ResetStyle() << "(Reset) to change speed";
    std::cout << eseq::cursor::MoveTo(13, game.getWidth() * 2 + gap) << "Use "
              << eseq::style::SetForeColor(eseq::style::colors::fore::BLUE)
              << "SPACE" << eseq::style::ResetStyle() << " to pause";
    std::cout << eseq::cursor::MoveTo(14, game.getWidth() * 2 + gap) << "Use "
              << eseq::style::SetForeColor(eseq::style::colors::fore::BLUE)
              << "ESC" << eseq::style::ResetStyle() << " to quit";
}

void flushCin(void) {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void flushKb(KbInput &keyboard) {
    while (keyboard.keyPressed())
        keyboard.getKey();
}

void printMenu_en(void) {
    std::cout
        << eseq::screen::ClearScreen() << eseq::cursor::MoveToHome()
        << "+ Ciallo~(∠・ω< )⌒☆  Ciallo~(∠・ω< )⌒☆  Ciallo~(∠・ω< )⌒☆ +\n"
        << "|                                                         |\n"
        << "|                    Lemony Snake Game                    |\n"
        << "|                                                         |\n"
        << "|                      Space - Start                      |\n"
        << "|                        Esc - Quit                       |\n"
        << "|                                                         |\n"
        << "+------------------- ↓ Custom Options ↓ ------------------+\n" // line8
        << "|                                                         |\n"
        << "|   (1)               Die if crash into self:             |\n" // line10
        << "|   (2)                    More kind of food:             |\n"
        << "|   (3)                            More food:             |\n"
        << "|   (4)     Health lost when crash into wall:             |\n"
        << "|   (5)               Generate boundary wall:             |\n"
        << "|   (6)             Generate additional wall:             |\n"
        << "|   (7)                           Coloration:             |\n"
        << "|   (8)                       Initial Length:             |\n"
        << "|   " << eseq::style::SetForeColor(eseq::style::colors::fore::GRAY)
        << "(↑ Press the corresponding key to switch value)"
        << eseq::style::ResetStyle() << "       |\n"
        << "|                                                         |\n"
        << "+---------------------------------------------------------+\n";
} //                                                          ^ col 50

std::string boolToString(bool b) {
    if (b)
        return "+";
    else
        return "-";
}

void printConfig(Game &game) {
    auto bTS = boolToString;
    std::cout << eseq::cursor::MoveTo(10, 48)
              << eseq::style::SetForeColor(eseq::style::colors::fore::GREEN)
              << bTS(game.dieIfCrashSelf) << eseq::style::ResetStyle();
    std::cout << eseq::cursor::MoveTo(11, 48)
              << eseq::style::SetForeColor(eseq::style::colors::fore::GREEN)
              << bTS(game.summonMoreKindOfFood) << eseq::style::ResetStyle();
    std::cout << eseq::cursor::MoveTo(12, 48)
              << eseq::style::SetForeColor(eseq::style::colors::fore::GREEN)
              << bTS(game.summonMoreFood) << eseq::style::ResetStyle();
    std::cout << eseq::cursor::MoveTo(13, 48)
              << eseq::style::SetForeColor(eseq::style::colors::fore::GREEN)
              << game.healthReducedByWall << eseq::style::ResetStyle()
              << "    ";
    std::cout << eseq::cursor::MoveTo(14, 48)
              << eseq::style::SetForeColor(eseq::style::colors::fore::GREEN)
              << bTS(game.generateBoundryWall) << eseq::style::ResetStyle();
    std::cout << eseq::cursor::MoveTo(15, 48)
              << eseq::style::SetForeColor(eseq::style::colors::fore::GREEN)
              << bTS(game.summonMoreWall) << eseq::style::ResetStyle();
    std::cout << eseq::cursor::MoveTo(16, 48)
              << eseq::style::SetForeColor(eseq::style::colors::fore::GREEN)
              << bTS(game.colorful) << eseq::style::ResetStyle();
    std::cout << eseq::cursor::MoveTo(17, 48)
              << eseq::style::SetForeColor(eseq::style::colors::fore::GREEN)
              << game.initLength << eseq::style::ResetStyle();
}

int nextValue(int current, std::vector<int> options) {
    int index = options.size() - 1;
    for (int i = 0; i < options.size(); i++) {
        if (options.at(i) == current) {
            index = i;
            break;
        }
    }
    return options.at((index + 1) % (options.size()));
}

void menuLoop(KbInput &keyboard, Game &game) {
    printMenu_en();
    unsigned long long loop_counter = 0;
    while (true) {
        bool update_flag = false;
        if (keyboard.keyPressed()) {
            update_flag = true;
            auto key = keyboard.getKey();
            if (key == 224) { // 上下左右键与功能键需要读两次
                key = keyboard.getKey();
            }
            switch (key) {
            case ' ':
                return;
                break;
            case 27:
                throw GameOver("exit signal by user");
                break;
            case '1':
                game.dieIfCrashSelf ^= true;
                break;
            case '2':
                game.summonMoreKindOfFood ^= true;
                break;
            case '3':
                game.summonMoreFood ^= true;
                break;
            case '4': {
                int &var = game.healthReducedByWall;
                var = nextValue(var, {-9999, -2, -1, 0});
            } break;
            case '5':
                game.generateBoundryWall ^= true;
                break;
            case '6':
                game.summonMoreWall ^= true;
                break;
            case '7':
                game.colorful ^= true;
                break;
            case '8': {
                int &var = game.initLength;
                var = nextValue(var, {1, 2, 3, 4, 5, 6});
            } break;
            default:
                break;
            }
        }
        if (loop_counter % 100 == 0) {
            printMenu_en();
            loop_counter %= 100;
            update_flag = true;
        }
        if (update_flag) {
            printConfig(game);
            std::cout << eseq::cursor::MoveToHome();
        }
        usleep(100 * 1000);
        loop_counter++;
    }
}
