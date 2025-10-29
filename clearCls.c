#include "clearCls.h"

void clearCls(){
    #ifdef _WIN32

    system("cls");

    #else

    system("clear");

    #endif
}