#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <io.h>
#include "football.h"

#define reddy_made

#ifdef reddy_made  
#define FILE_NAME "REDDYLAB_6.bin"  // Используется, если определён макрос reddy_made  
#else  
#define FILE_NAME "footballers.bin"  // Используется, если макрос reddy_made не определён  
#endif  

// Удаление символа новой строки
void removeNewline(char* str) {
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}
//Проверка размера файла
int isFileEmpty() {
    FILE* f = fopen(FILE_NAME, "rb");
    if (!f) {
        printf("Error opening file\n");
        return 1;  // Считаем файл "пустым" при ошибке открытия
    }

    fseek(f, 0, SEEK_END);
    long fileSize = ftell(f);
    fclose(f);

    return (fileSize == 0);
}
// Добавление футболиста
void addFootballer() {
    FILE* f = fopen(FILE_NAME, "a+b");
    if (!f) {
        printf("Error opening file\n");
        return;
    }

    Footballer footballer;
    printf("How many footballers do you want to add? ");
    int count;
    scanf("%d", &count);
    while (getchar() != '\n');

    for (int i = 0; i < count; i++) {
        printf("Enter full name: ");
        fgets(footballer.fullName, sizeof(footballer.fullName), stdin);
        removeNewline(footballer.fullName);

        printf("Enter club name: ");
        fgets(footballer.clubName, sizeof(footballer.clubName), stdin);
        removeNewline(footballer.clubName);

        printf("Enter position (goalkeeper, defender, midfielder, forward): ");
        fgets(footballer.position, sizeof(footballer.position), stdin);
        removeNewline(footballer.position);

        printf("Enter age: ");
        scanf("%d", &footballer.age);
        while (getchar() != '\n');

        printf("Enter matches played: ");
        scanf("%d", &footballer.matchesPlayed);
        while (getchar() != '\n');

        printf("Enter goals scored: ");
        scanf("%d", &footballer.goalsScored);
        while (getchar() != '\n');

        fwrite(&footballer, sizeof(Footballer), 1, f);
    }

    fclose(f);
    printf("Footballers added successfully!\n");
}

// Отображение футболистов
void displayFootballers() {
    FILE* f = fopen(FILE_NAME, "rb");
    if (!f) {
        printf("Error opening file\n");
        return;
    }
     // Вычисляем количество записей
     fseek(f, 0, SEEK_END);
     long fileSize = ftell(f);
     int totalFootballers = fileSize / sizeof(Footballer);
     rewind(f);
 
     // Проверка на пустой список
     if (totalFootballers == 0) {
         printf("The list of footballers is empty!\n");
         fclose(f);
         return;
     }

    Footballer footballer;
    int number = 0;

    printf("---------------------------------------------------------------------------------------------------------------\n");
    printf("| %-3s | %-20s | %-20s | %-13s | %-4s | %-14s | %-15s |\n",
        "N", "Full Name", "Club Name", "Position", "Age", "Matches Played", "Goals Scored");
    printf("---------------------------------------------------------------------------------------------------------------\n");

    while (fread(&footballer, sizeof(Footballer), 1, f)) {
        number++;
        printf("| %-3d | %-20s | %-20s | %-13s | %-4d | %-14d | %-15d |\n",
            number, footballer.fullName, footballer.clubName, footballer.position, 
            footballer.age, footballer.matchesPlayed, footballer.goalsScored);
        printf("---------------------------------------------------------------------------------------------------------------\n");    
    }

    fclose(f);
}

// Создание начальных данных
void createInitialData() {
    FILE* f = fopen(FILE_NAME, "wb");
    if (!f) {
        printf("Error creating file\n");
        return;
    }

    Footballer footballers[] = {
        {"Lionel Messi", "PSG", "forward", 36, 172, 98},
        {"Cristiano Ronaldo", "Al Nassr", "forward", 38, 196, 123},
        {"Kylian Mbappe", "PSG", "forward", 24, 86, 42},
        {"Kevin De Bruyne", "Manchester City", "midfielder", 31, 112, 28},
        {"Virgil van Dijk", "Liverpool", "defender", 31, 97, 12}
    };

    fwrite(footballers, sizeof(Footballer), 5, f);
    fclose(f);
    printf("Initial footballer database created successfully!\n");
}

// Редактирование футболиста
void editFootballer(int position) {
    if (isFileEmpty()) {
        printf("The database is empty. No footballers to search.\n");
        return;
    }
    FILE* f = fopen(FILE_NAME, "rb+");
    if (!f) {
        printf("Error opening file\n");
        return;
    }

    fseek(f, position * sizeof(Footballer), SEEK_SET);

    Footballer footballer;
    fread(&footballer, sizeof(Footballer), 1, f);

    int choice;
    printf("\n1. Change Full Name\n2. Change Club Name\n3. Change Position\n4. Change Age\n5. Change Matches Played\n6. Change Goals Scored\n");
    scanf("%d", &choice);
    while (getchar() != '\n');

    switch (choice) {
        case 1:
            printf("Enter new full name: ");
            fgets(footballer.fullName, sizeof(footballer.fullName), stdin);
            removeNewline(footballer.fullName);
            break;
        case 2:
            printf("Enter new club name: ");
            fgets(footballer.clubName, sizeof(footballer.clubName), stdin);
            removeNewline(footballer.clubName);
            break;
        case 3:
            printf("Enter new position: ");
            fgets(footballer.position, sizeof(footballer.position), stdin);
            removeNewline(footballer.position);
            break;
        case 4:
            printf("Enter new age: ");
            scanf("%d", &footballer.age);
            break;
        case 5:
            printf("Enter new matches played: ");
            scanf("%d", &footballer.matchesPlayed);
            break;
        case 6:
            printf("Enter new goals scored: ");
            scanf("%d", &footballer.goalsScored);
            break;
    }

    fseek(f, position * sizeof(Footballer), SEEK_SET);
    fwrite(&footballer, sizeof(Footballer), 1, f);
    fclose(f);
}

// Удаление футболиста
void deleteFootballer() {
    if (isFileEmpty()) {
        printf("The database is empty. Nothing to delete.\n");
        return;
    }
    FILE* f = fopen(FILE_NAME, "rb+");
    if (!f) {
        printf("Error opening file\n");
        return;
    }

    fseek(f, 0, SEEK_END);
    long fileSize = ftell(f);
    int totalFootballers = fileSize / sizeof(Footballer);

    printf("Enter the number of the footballer to delete: ");
    int position;
    scanf("%d", &position);
    while (getchar() != '\n');

    if (position < 1 || position > totalFootballers) {
        printf("Invalid position\n");
        fclose(f);
        return;
    }

    position -= 1;
    Footballer tempFootballer;

    for (int i = position + 1; i < totalFootballers; i++) {
        fseek(f, i * sizeof(Footballer), SEEK_SET);
        fread(&tempFootballer, sizeof(Footballer), 1, f);
        fseek(f, (i - 1) * sizeof(Footballer), SEEK_SET);
        fwrite(&tempFootballer, sizeof(Footballer), 1, f);
    }

    _chsize(_fileno(f), fileSize - sizeof(Footballer));
    fclose(f);
    printf("Footballer deleted successfully!\n");
}

// Функции сравнения для поиска
int compareFullName(Footballer* footballer, void* searchValue) {
    return strcmp(footballer->fullName, (char*)searchValue) == 0;
}

int compareClubName(Footballer* footballer, void* searchValue) {
    return strcmp(footballer->clubName, (char*)searchValue) == 0;
}

int comparePosition(Footballer* footballer, void* searchValue) {
    return strcmp(footballer->position, (char*)searchValue) == 0;
}

int compareAge(Footballer* footballer, void* searchValue) {
    return footballer->age == *(int*)searchValue;
}

int compareMatchesPlayed(Footballer* footballer, void* searchValue) {
    return footballer->matchesPlayed == *(int*)searchValue;
}

int compareGoalsScored(Footballer* footballer, void* searchValue) {
    return footballer->goalsScored == *(int*)searchValue;
}

// Поиск футболиста
void searchFootballer() {
    if (isFileEmpty()) {
        printf("The database is empty. No footballers to search.\n");
        return;
    }
    FILE* f = fopen(FILE_NAME, "rb");
    if (!f) {
        printf("Error opening file\n");
        return;
    }
    int choice;
    printf("\nSearch by:\n1. Full Name\n2. Club Name\n3. Position\n4. Age\n5. Matches Played\n6. Goals Scored\n");
    scanf("%d", &choice);
    while (getchar() != '\n');

    int (*compareFuncs[])(Footballer*, void*) = {
        compareFullName, compareClubName, comparePosition,
        compareAge, compareMatchesPlayed, compareGoalsScored
    };

    void* searchValue = NULL;
    char searchStr[50];
    int searchInt;

    if (choice >= 1 && choice <= 6) {
        if (choice >= 4 && choice <= 6) {
            printf("Enter search value: ");
            scanf("%d", &searchInt);
            while (getchar() != '\n');
            searchValue = &searchInt;
        } else {
            printf("Enter search value: ");
            fgets(searchStr, sizeof(searchStr), stdin);
            removeNewline(searchStr);
            searchValue = searchStr;
        }
    }

    Footballer footballer;
    int found = 0;

    printf("---------------------------------------------------------------------------------------------------------------\n");
    printf("| %-3s | %-20s | %-20s | %-13s | %-4s | %-14s | %-15s |\n",
        "N", "Full Name", "Club Name", "Position", "Age", "Matches Played", "Goals Scored");
    printf("---------------------------------------------------------------------------------------------------------------\n");

    while (fread(&footballer, sizeof(Footballer), 1, f)) {
        if (compareFuncs[choice - 1](&footballer, searchValue)) {
            printf("%-20s %-20s %-13s %-4d %-14d %-15d\n",
                footballer.fullName, footballer.clubName, footballer.position,
                footballer.age, footballer.matchesPlayed, footballer.goalsScored);
            found = 1;
        }
    }

    if (!found) {
        printf("No footballer found with the given criteria.\n");
    }

    fclose(f);
}

// Меню управления футболистами
void footballerMenu() {
    int choice = 0;

    while (1) {
        printf("\nFootballer Management Menu:\n");
        printf("1. Add Footballer\n");
        printf("2. Display Footballers\n");
        printf("3. Search Footballer\n");
        printf("4. Edit Footballer\n");
        printf("5. Delete Footballer\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");

        scanf("%d", &choice);
        while (getchar() != '\n');

        switch (choice) {
            case 1: addFootballer(); break;
            case 2: displayFootballers(); break;
            case 3: searchFootballer(); break;
            case 4: 
                printf("Enter footballer number to edit: ");
                int position;
                scanf("%d", &position);
                while (getchar() != '\n');
                editFootballer(position - 1);
                break;
            case 5: deleteFootballer(); break;
            case 6: return;
            default: printf("Invalid choice. Try again.\n");
        }
    }
}

// Основная функция
int main() {
    printf("%d", sizeof(Footballer));
    #ifdef reddy_made  
    // Если определена макроконстанта reddy_made, вызываем функцию createIGuestData()
    createInitialData();
#endif
    footballerMenu();
    
    return 0;
}
