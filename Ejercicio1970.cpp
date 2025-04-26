#include <vector>
#include <iostream>
#include <stack>
using namespace std;
class Solution {
public:
    int latestDayToCross(int row, int col, vector<vector<int>>& cells) {
        vector<vector<int>> matriz = crearMatrizDeCeros(row, col);
        int count = 0;

        for (const auto& cell : cells) {
            int r = cell[0] - 1; // Convertir a índice 0-based
            int c = cell[1] - 1;

            matriz[r][c] = 1; // Bloquear la celda

            if (existeCaminoDFS(matriz)) {
                count++;
            } else {
                break;
            }
        }
        return count;
    }
    vector<vector<int>> crearMatrizDeCeros(int rows, int cols) {
        vector<vector<int>> matriz(rows, vector<int>(cols, 0));
        return matriz;
    }

    bool existeCaminoDFS(const vector<vector<int>>& matriz) {
        if (matriz.empty() || matriz[0].empty()) return false;

        int filas = matriz.size();
        int columnas = matriz[0].size();

        vector<vector<bool>> visitado(filas, vector<bool>(columnas, false));
        vector<pair<int, int>> direcciones = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        stack<pair<int, int>> pila;

        for (int c = 0; c < columnas; ++c) {
            if (matriz[0][c] == 0) {
                pila.push({0, c});
                visitado[0][c] = true;
                while (!pila.empty()) {
                    auto actual = pila.top();
                    pila.pop();
                    int fila = actual.first;
                    int col = actual.second;

                    if (fila == filas - 1) {
                        return true;
                    }

                    for (const auto& dir : direcciones) {
                        int nuevaFila = fila + dir.first;
                        int nuevaCol = col + dir.second;

                        if (nuevaFila >= 0 && nuevaFila < filas &&
                            nuevaCol >= 0 && nuevaCol < columnas &&
                            matriz[nuevaFila][nuevaCol] == 0 &&
                            !visitado[nuevaFila][nuevaCol]) {
                            visitado[nuevaFila][nuevaCol] = true;
                            pila.push({nuevaFila, nuevaCol});
                        }
                    }
                }
                visitado = vector<vector<bool>>(filas, vector<bool>(columnas, false));
            }
        }
        return false;
    }
};

int main(){
    Solution solution;
    vector<vector<int>> cells = {{1,1},{1,2},{2,1},{2,2}};
    int rows = 2;
    int cols = 2;
    vector<vector<int>> ceros = solution.crearMatrizDeCeros(rows,cols);
    cout << solution.latestDayToCross(rows,cols,cells);

}
