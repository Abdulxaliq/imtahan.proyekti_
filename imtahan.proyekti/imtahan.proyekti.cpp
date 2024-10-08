#include <iostream>
#include <ctime>
#include <cstdlib>
#include <conio.h>

using namespace std;

const int BOARD_SIZE = 10;
const int SHIP_SIZES[] = { 4, 3, 3, 2, 2, 2, 1, 1, 1, 1 };
const int SHIP_COUNT = sizeof(SHIP_SIZES) / sizeof(SHIP_SIZES[0]);

void initializeBoard(char board[BOARD_SIZE][BOARD_SIZE]) {
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            board[i][j] = '+';
        }
    }
}

bool canPlaceShip(char board[BOARD_SIZE][BOARD_SIZE], int x, int y, int size, bool vertical) {
    if (vertical) {
        if (x + size > BOARD_SIZE) return false;
        for (int i = 0; i < size; ++i) {
            if (board[x + i][y] != '+') return false;
        }
    }
    else {
        if (y + size > BOARD_SIZE) return false;
        for (int i = 0; i < size; ++i) {
            if (board[x][y + i] != '+') return false;
        }
    }
    return true;
}

void placeShip(char board[BOARD_SIZE][BOARD_SIZE], int x, int y, int size, bool vertical) {
    if (vertical) {
        for (int i = 0; i < size; ++i) {
            board[x + i][y] = 'S';
        }
    }
    else {
        for (int i = 0; i < size; ++i) {
            board[x][y + i] = 'S';
        }
    }
}

void printBoard(char board[BOARD_SIZE][BOARD_SIZE], int cursorX = -1, int cursorY = -1, bool showShips = false) {
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            if (i == cursorX && j == cursorY) {
                cout << "C ";
            }
            else if (showShips && board[i][j] == 'S') {
                cout << "\033[35mS ";
            }
            else if (board[i][j] == 'A') {
                cout << "\033[32mA ";
            }
            else if (board[i][j] == 'M') {
                cout << "\033[31mM ";
            }
            else {
                cout << "\033[36m~ ";
            }
        }
        cout << endl;
    }
}

void placeShipsManual(char board[BOARD_SIZE][BOARD_SIZE]) {
    int x = 0, y = 0;
    char input;
    int shipIndex = 0;
    bool vertical = false;

    while (shipIndex < SHIP_COUNT) {
        int size = SHIP_SIZES[shipIndex];

        system("cls");
        printBoard(board, x, y, true);
        cout << "Geminin uzunlugu: " << size << endl;
        cout << "Daxil edin (Enter ile yerlestirin, r ile yon deyisdirin): " << endl;
        input = _getch();

        switch (input) {
        case 72:
            x = (x - 1 + BOARD_SIZE) % BOARD_SIZE;
            break;
        case 80:
            x = (x + 1) % BOARD_SIZE;
            break;
        case 75:
            y = (y - 1 + BOARD_SIZE) % BOARD_SIZE;
            break;
        case 77:
            y = (y + 1) % BOARD_SIZE;
            break;
        case 13:
            if (canPlaceShip(board, x, y, size, vertical)) {
                placeShip(board, x, y, size, vertical);
                shipIndex++;
            }
            else {
                cout << "Bura yerlesdirmek olmaz. Yeniden edin." << endl;
                system("pause");
            }
            break;
        case 'r':
            vertical = !vertical;
            break;
        }
    }
}

bool takeShot(char board[BOARD_SIZE][BOARD_SIZE], int x, int y) {
    if (board[x][y] == 'S') {
        board[x][y] = 'A';
        return true;
    }
    else if (board[x][y] == '+') {
        board[x][y] = 'M';
        return false;
    }
    else {
        cout << "Bu kordinata onsuzda vurmusunuz!" << endl;
        return false;
    }
}

bool allShipsSunk(char board[BOARD_SIZE][BOARD_SIZE]) {
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            if (board[i][j] == 'S') {
                return false;
            }
        }
    }
    return true;
}

void selectCoordinate(char board[BOARD_SIZE][BOARD_SIZE], int& x, int& y) {
    int cursorX = 0, cursorY = 0;
    char input;

    while (true) {
        system("cls");
        printBoard(board, cursorX, cursorY, false);
        cout << "\033[34mKoordinatlari mueyyen edin (oxlarla istifade edin ve enter basin):" << endl;
        cout << "\033[32mKoordinat : (" << cursorX << ", " << cursorY << ")" << endl;

        input = _getch();
        switch (input) {
        case 72:
            cursorX = (cursorX - 1 + BOARD_SIZE) % BOARD_SIZE;
            break;
        case 80:
            cursorX = (cursorX + 1) % BOARD_SIZE;
            break;
        case 75:
            cursorY = (cursorY - 1 + BOARD_SIZE) % BOARD_SIZE;
            break;
        case 77:
            cursorY = (cursorY + 1) % BOARD_SIZE;
            break;
        case 13:
            x = cursorX;
            y = cursorY;
            return;
        }
    }
}

void placeShipsRandom(char board[BOARD_SIZE][BOARD_SIZE]) {
    srand((time(0)));
    for (int shipIndex = 0; shipIndex < SHIP_COUNT; ++shipIndex) {
        int size = SHIP_SIZES[shipIndex];
        bool placed = false;

        while (!placed) {
            int x = rand() % BOARD_SIZE;
            int y = rand() % BOARD_SIZE;
            bool vertical = rand() % 2;

            if (canPlaceShip(board, x, y, size, vertical)) {
                placeShip(board, x, y, size, vertical);
                placed = true;
            }
        }
    }
}

void displayWelcomeMenu() {
    int selectedOption = 0;
    char input;
    string options[2] = { "\033[31mOyuna Basla", "\033[32mCixis" };

    while (true) {
        system("cls");
        cout << "\033[34mXos Gelmisiniz!" << endl;
        for (int i = 0; i < 2; ++i) {
            if (i == selectedOption) {
                cout << "\033[0m> " << options[i] << "\033[0m <" << endl;
            }
            else {
                cout << options[i] << endl;
            }
        }

        input = _getch();

        if (input == 72) selectedOption = (selectedOption - 1 + 2) % 2;
        else if (input == 80) selectedOption = (selectedOption + 1) % 2;
        else if (input == 13) {
            if (selectedOption == 0) {
                return;
            }
            else {
                exit(0);
            }
        }
    }
}

void chooseShipPlacement(char board[BOARD_SIZE][BOARD_SIZE]) {
    int selectedOption = 0;
    char input;
    string options[2] = { "\033[31mManual", "\033[32mRandom" };

    while (true) {
        system("cls");
        cout << "\033[34mOyuncu: 1" << endl;
        cout << "\033[0mGemileri yerlesdirmek ucun secim edin:" << endl;
        for (int i = 0; i < 2; ++i) {
            if (i == selectedOption) {
                cout << "\033[0m> " << options[i] << "\033[0m <" << endl;
            }
            else {
                cout << options[i] << endl;
            }
        }

        input = _getch();
        if (input == 72) selectedOption = (selectedOption - 1 + 2) % 2;
        else if (input == 80) selectedOption = (selectedOption + 1) % 2;
        else if (input == 13) {
            if (selectedOption == 0) {
                placeShipsManual(board);
            }
            else if (selectedOption == 1) {
                placeShipsRandom(board);
            }
            break;
        }
    }
}

void displayTurnMessage(bool player2Turn) {
    system("cls");
    cout << (player2Turn ? "===== Oyuncu 2'nin Sirasi =====" : "===== Oyuncu 1'in Sirasi =====") << endl;
    cout << "Davam etmek ucun hansisa duymeye basin..." << endl;
    _getch();
}


int main() {
    char board1[BOARD_SIZE][BOARD_SIZE];
    char board2[BOARD_SIZE][BOARD_SIZE];

    displayWelcomeMenu();

    cout << "Oyuncu 1:" << endl;
    initializeBoard(board1);
    chooseShipPlacement(board1);

    cout << "Oyuncu 2:" << endl;
    initializeBoard(board2);
    chooseShipPlacement(board2);

    int x, y;
    bool player1Turn = true;

    while (!allShipsSunk(board1) && !allShipsSunk(board2)) {
        displayTurnMessage(!player1Turn);

        printBoard(player1Turn ? board2 : board1, -1, -1, false);

        selectCoordinate(player1Turn ? board2 : board1, x, y);
        bool hit = takeShot(player1Turn ? board2 : board1, x, y);

        if (hit) {
            cout << "Hit!" << endl;
        }
        else {
            cout << "Olmadı!" << endl;
            player1Turn = !player1Turn;
        }

        if (allShipsSunk(board2)) {
            cout << "Oyuncu 1 kazandı! Tebrikler!!!!!!!!!!!" << endl;
            break;
        }
        else if (allShipsSunk(board1)) {
            cout << "Oyuncu 2 kazandı! Tebrikler!!!!!!!!!" << endl;
            break;
        }
    }

    cout << "Oyun Bitti!" << endl;
    return 0;
}