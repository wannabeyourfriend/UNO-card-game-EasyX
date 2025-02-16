# include <iostream>
# include "uno_logic.h"
# include "visualize.h"
#include <windows.h>
#pragma comment(lib,"Winmm.lib")
using namespace std;

int main() {
    printf("Welcome to UNO!");
    mciSendString(_T("open music.mp3 alias bkmusic"), NULL, 0, NULL);//≤•∑≈“Ù¿÷
    mciSendString(_T("play bkmusic repeat"), NULL, 0, NULL);//—≠ª∑≤•∑≈
    initialize_card_image();
    initialize_color_card_image();
    initialize_player_image();
    Application application = Application(initialize_startgame());
    initialize_color_card_image();
    application.gameLoop();
    system("pause");
    return 0;
}

