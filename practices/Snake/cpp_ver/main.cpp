#include "./main.hpp"

void prepare(void) {
    std::cout.setf(std::ios::unitbuf);
#if defined(_WIN32) || defined(_WIN64)
    SetConsoleOutputCP(CP_UTF8);
#else

#endif
}
void gameLoop(KbInput &keyboard, Game &game) {
    int delay = 200 * 1000; // nanosec
    std::cout << eseq::cursor::MoveToHome() << eseq::screen::ClearScreen();
    game.start();
    unsigned int frame_count = 0;

    while (true) {
        if (!game.isAlive())
            return;
        if (keyboard.keyPressed()) {
            auto key = keyboard.getKey();
            // if (key == 224) { // 上下左右键与功能键需要读两次
            //     key = keyboard.getKey();
            // }
            switch (key) {
            case 'W':
            case 'w':
            // case 72:
            case 'S':
            case 's':
            // case 80:
            case 'A':
            case 'a':
            // case 75:
            case 'D':
            case 'd':
                // case 77:
                game.operate(key);
                break;
            case ' ':
                flushKb(keyboard);
                std::cout << eseq::cursor::MoveTo(game.getHeight() + 1, 1)
                          << "Press any key to resume...";
                keyboard.getKey();
                std::cout << eseq::cursor::MoveTo(game.getHeight() + 1, 1)
                          << eseq::screen::ClearLine();
                flushKb(keyboard);
                break;
            case 'Q':
            case 'q':
                delay *= 1.1;
                break;
            case 'E':
            case 'e':
                delay *= 0.9;
                break;
            case 'R':
            case 'r':
                delay = 200 * 1000;
                break;
            case 27: // esc
                flushKb(keyboard);
                return;
            }
            flushKb(keyboard);
        }
        usleep(delay);
        game.nextFrame();

        if (frame_count % 100 == 0)
            std::cout << eseq::screen::ClearScreen();
        printTips(game);
        std::cout << eseq::cursor::MoveToHome() << game.render();
        printStatus(game, delay);
        frame_count++;
    }
}

void showNotice(KbInput &keyboard) {
    flushKb(keyboard);
    std::cout << eseq::screen::ClearScreen() << eseq::cursor::MoveToHome();
    std::cout << "Hi there!\n"
              << "Plz expand the window large enough, or reduce font size,\n"
                 "                               ...to fit the game stage.\n";
#if defined(_WIN32) || defined(_WIN64)
#else
    std::cout << "\nIt looks like you are playing this game on Linux :)\n"
              << "Please do not use special key like arrow keys, which may "
                 "lead to abnormal behaviors on Linux\n"
              << "I will try to fix this later.";
#endif
    std::cout << "\nPress any key to continue.";
    keyboard.getKey();
    flushKb(keyboard);
}

int main(void) {
    prepare();
    auto keyboard = KbInput();
    flushKb(keyboard);
    showNotice(keyboard);
    while (true) {
        Game game = Game(40, 40);
        if (!menuLoop(keyboard, game)) {
            std::cout << eseq::screen::ClearScreen()
                      << "Thank you for playing..." << std::endl;
            // usleep(2 * 1000 * 1000);
            return 0;
        }
        gameLoop(keyboard, game);
        std::cout << eseq::cursor::MoveTo(
                         game.getHeight() / 2,
                         game.getWidth() -
                             (game.getCauseOfDeath().length() / 2))
                  << game.getCauseOfDeath();
        std::cout << eseq::cursor::MoveTo(game.getHeight() + 1, 1)
                  << "Press any key to continue...";
        flushKb(keyboard);
        keyboard.getKey();
    }
    return 0;
}
