#include "./main.hpp"

void prepare(void) {
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
        if (keyboard.keyPressed()) {
            auto key = keyboard.getKey();
            if (key == 224) { // 上下左右键与功能键需要读两次
                key = keyboard.getKey();
            }
            switch (key) {
            case 'W':
            case 'w':
            case 72:
            case 'S':
            case 's':
            case 80:
            case 'A':
            case 'a':
            case 75:
            case 'D':
            case 'd':
            case 77:
                game.operate(key);
                break;
            case ' ':
                std::cout << eseq::cursor::MoveTo(game.getHeight() + 1, 1)
                          << "Press any key to resume...";
                keyboard.getKey();
                std::cout << eseq::cursor::MoveTo(game.getHeight() + 1, 1)
                          << eseq::screen::ClearLine();
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
                throw GameOver("terminated by user");
                break;
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
                 "                               ...to fit the game stage.\n"
              << "Press any key to continue.";
    keyboard.getKey();
    flushKb(keyboard);
}

int main(void) {
    prepare();
    auto keyboard = KbInput();
    showNotice(keyboard);
    while (true) {
        Game game = Game(40, 40);
        try {
            menuLoop(keyboard, game);
        } catch (const GameOver &e) {
            std::cout << eseq::screen::ClearScreen()
                      << "Thank you for playing...";
            usleep(2 * 1000 * 1000);
            return 0;
        }
        try {
            gameLoop(keyboard, game);
        } catch (const GameOver &e) {
            std::cout << eseq::cursor::MoveTo(
                             game.getHeight() -
                                 (std::string(e.what()).length() / 2),
                             game.getWidth() / 2)
                      << e.what();
        }
        std::cout << eseq::cursor::MoveTo(game.getHeight() + 1, 1)
                  << "Press any key to continue...";
        flushKb(keyboard);
        keyboard.getKey();
    }
    return 0;
}
