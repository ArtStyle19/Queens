#include <iostream>
#include <vector>

using namespace std;

const int N = 5;
vector<int> queens(N); 

bool isValid(int row, int col) {
    for (int i = 0; i < col; ++i) {
        if (queens[i] == row || abs(queens[i] - row) == abs(i - col)) {
            return false; 
        }
    }
    return true;
}

// Función para mover las reinas horizontalmente por sus filas
bool moveQueens(int col) {
    if (col >= N) {
        return true; 
    }
    for (int i = 0; i < N; ++i) {
        if (isValid(i, col)) {
            int old_row = queens[col]; 
            queens[col] = i; 
            
            cout << "Matriz después de colocar la reina " << col << ":" << endl;
            for (int i = 0; i < N; ++i) {
                for (int j = 0; j < N; ++j) {
                    if (queens[j] == i) {
                        cout << "1 ";
                    } else {
                        cout << "0 ";
                    }
                }
                cout << endl;
            }
            cout << endl;
            
            if (moveQueens(col + 1)) {
                // Se encontró solucion
                for (int j = 0; j < col; ++j) {
                    int diff = old_row - queens[j];
                    cout << "Reina " << j << " se mueve ";
                    if (diff > 0) {
                        cout << "hacia atrás " << diff << " veces.\n";
                    } else if (diff < 0) {
                        cout << "hacia adelante " << -diff << " veces.\n";
                    } else {
                        cout << "no se mueve.\n";
                    }
                }
                return true;
            }
            queens[col] = old_row; 
        }
    }
    return false; 
}

int main() {
    queens = {4, 0, 4, 0, 4};

    if (moveQueens(0)) {
        cout << "Solución encontrada:\n";
        for (int i = 0; i < N; ++i) {
            cout << "Reina " << i << " se mueve a fila " << queens[i] + 1 << "\n";
        }

        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                if (queens[j] == i) {
                    cout << "1 ";
                } else {
                    cout << "0 ";
                }
            }
            cout << endl;
        }
    } else {
        cout << "No se encontró ninguna solución.\n";
    }
    return 0;
}
