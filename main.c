#include "football.h"
#include <stdio.h> 

// Основная функция
int main() {
#ifdef reddy_made
    // Если определена макроконстанта reddy_made, вызываем функцию createIGuestData()
    createInitialData();
#endif
    footballerMenu();
    
    return 0;
}
