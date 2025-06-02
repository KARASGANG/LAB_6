#ifndef FOOTBALL_H
#define FOOTBALL_H

#define _CRT_SECURE_NO_WARNINGS

typedef struct {
    char fullName[33];     // ФИО футболиста
    char clubName[20];     // Название клуба
    char position[20];     // Амплуа
    int age;               // Возраст
    int matchesPlayed;     // Количество проведенных матчей
    int goalsScored;       // Количество забитых мячей
} Footballer;

// Прототипы функций
void addFootballer();
void displayFootballers();
void createInitialData();
void editFootballer(int position);
void deleteFootballer();
void searchFootballer();
void footballerMenu();

// Функции сравнения для поиска
int compareFullName(Footballer* footballer, void* searchValue);
int compareClubName(Footballer* footballer, void* searchValue);
int comparePosition(Footballer* footballer, void* searchValue);
int compareAge(Footballer* footballer, void* searchValue);
int compareMatchesPlayed(Footballer* footballer, void* searchValue);
int compareGoalsScored(Footballer* footballer, void* searchValue);

#endif // FOOTBALL_H
