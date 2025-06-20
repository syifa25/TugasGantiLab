#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

const int SIZE = 6;
const int MIN_BOM = 5;
const int MAX_BOM = 10;

class Minesweeper {
private:
    int data[SIZE][SIZE];
    char board[SIZE][SIZE];
    bool revealed[SIZE][SIZE];
    int jumlahBom;

public:
    Minesweeper(int bom) {
        jumlahBom = bom;
        srand(time(0));
        initBoard();
        generateBoard();
    }

    void initBoard() {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                data[i][j] = 0;
                board[i][j] = '*';
                revealed[i][j] = false;
            }
        }
    }

    void generateBoard() {
        int bomTerpasang = 0;
        while (bomTerpasang < jumlahBom) {
            int r = rand() % SIZE;
            int c = rand() % SIZE;

            if (data[r][c] == -1) continue;

            data[r][c] = -1;
            bomTerpasang++;

            for (int i = -1; i <= 1; i++) {
                for (int j = -1; j <= 1; j++) {
                    int dr = r + i;
                    int dc = c + j;
                    if (dr >= 0 && dr < SIZE && dc >= 0 && dc < SIZE && data[dr][dc] != -1) {
                        data[dr][dc]++;
                    }
                }
            }
        }
    }

    void displayBoard() {
        cout << "  0 1 2 3 4 5\n";
        for (int i = 0; i < SIZE; i++) {
            cout << i << " ";
            for (int j = 0; j < SIZE; j++) {
                if (revealed[i][j]) {
                    cout << board[i][j] << " ";
                } else {
                    cout << "* ";
                }
            }
            cout << endl;
        }
    }

    bool openCell(int row, int col) {
        if (revealed[row][col]) {
            cout << "Kotak sudah dibuka. Pilih kotak lain.\n";
            return true;
        }

        revealed[row][col] = true;

        if (data[row][col] == -1) {
            board[row][col] = 'X';
            return false;
        } else {
            board[row][col] = data[row][col] + '0';
            return true;
        }
    }

    bool isWin() {
        int count = 0;
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (revealed[i][j]) count++;
            }
        }
        return count == (SIZE * SIZE - jumlahBom);
    }
};

int main() {
    int jumlahBom;
    cout << "Masukkan jumlah bom (5-10): ";
    cin >> jumlahBom;
    while (jumlahBom < MIN_BOM || jumlahBom > MAX_BOM) {
        cout << "Jumlah bom tidak valid. Masukkan antara 5 sampai 10: ";
        cin >> jumlahBom;
    }

    Minesweeper game(jumlahBom);

    bool gameOn = true;
    while (gameOn) {
        game.displayBoard();
        int row, col;
        cout << "Tebak baris dan kolom (contoh: 2 3): "; 
        cin >> row >> col;
        
        if (row < 0 || row >= SIZE || col < 0 || col >= SIZE) {
            cout << "Input di luar batas. Coba lagi.\n";
            continue;
        }

        bool aman = game.openCell(row, col);
        if (!aman) {
            cout << "BOOM! Kamu terkena bom. GAME OVER!\n";
            game.displayBoard();
            break;
        }

        if (game.isWin()) {
            cout << "Selamat! Kamu berhasil membuka semua kotak aman. MENANG!\n";
            game.displayBoard();
            break;
        }
    }

    return 0;
}
