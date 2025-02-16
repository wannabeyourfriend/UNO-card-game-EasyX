#include <iostream>
#include "uno_logic.h"

int main() {
    Application application = Application(5);
    application.gameLoop();
    system("pause");
    return 0;
}