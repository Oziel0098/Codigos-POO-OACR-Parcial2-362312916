#include <stdio.h>
#include <conio.h>
#include <fstream>
#include <string.h>

const int MAX = 100;
char lab[MAX][MAX];
bool visitado[MAX][MAX];
int filaAnterior[MAX][MAX];
int colAnterior[MAX][MAX];

int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

struct Punto 
{
    int fila, col;
};

Punto cola[MAX * MAX];
int frente = 0, fin = 0;

bool esValido(int x, int y, int filas, int cols) 
{
    return x >= 0 && y >= 0 && x < filas && y < cols &&
           !visitado[x][y] && (lab[x][y] == ' ' || lab[x][y] == 'F');
}

void trazarCamino(int ix, int iy, int fx, int fy) 
{
    while (!(ix == fx && iy == fy)) 
	{
        if (lab[fx][fy] != 'F') lab[fx][fy] = 'o';
        int px = filaAnterior[fx][fy];
        int py = colAnterior[fx][fy];
        fx = px;
        fy = py;
    }
}

int main() 
{
    char nombreArchivo[100];
    printf("Ingresa el nombre del archivo del laberinto: ");
    gets(nombreArchivo);

    std::ifstream archivo(nombreArchivo);
    if (!archivo) 
	{
        printf("No se pudo abrir el archivo.\n");
        getch();
        return 1;
    }

    int filas = 0;
    int maxCols = 0;
    char linea[MAX];

    // Leer el laberinto y detectar longitud máxima
    while (archivo.getline(linea, MAX)) 
	{
        int len = strlen(linea);
        if (len > maxCols) maxCols = len;

        // Copiar línea a laberinto
        for (int j = 0; j < len; j++) 
		{
            lab[filas][j] = linea[j];
        }

        filas++;
    }

    int inicioX = -1, inicioY = -1, finX = -1, finY = -1;

    // Buscar 'I' y 'F'
    for (int i = 0; i < filas; i++) 
	{
        for (int j = 0; j < maxCols; j++) 
		{
            if (lab[i][j] == 'I') 
			{
                inicioX = i;
                inicioY = j;
            }
            if (lab[i][j] == 'F') 
			{
                finX = i;
                finY = j;
            }
        }
    }

    if (inicioX == -1 || finX == -1) 
	{
        printf("No se encontró el punto de inicio (I) o fin (F).\n");
        getch();
        return 1;
    }

    // BFS
    cola[fin++] = {inicioX, inicioY};
    visitado[inicioX][inicioY] = true;

    while (frente < fin) 
	{
        Punto actual = cola[frente++];
        if (actual.fila == finX && actual.col == finY) break;

        for (int d = 0; d < 4; d++) 
		{
            int nx = actual.fila + dx[d];
            int ny = actual.col + dy[d];

            if (esValido(nx, ny, filas, maxCols)) 
			{
                visitado[nx][ny] = true;
                filaAnterior[nx][ny] = actual.fila;
                colAnterior[nx][ny] = actual.col;
                cola[fin++] = {nx, ny};
            }
        }
    }

    trazarCamino(inicioX, inicioY, finX, finY);

    // Mostrar laberinto con camino
    for (int i = 0; i < filas; i++) 
	{
        for (int j = 0; j < maxCols; j++) 
		{
            putchar(lab[i][j]);
        }
        putchar('\n');
    }

    getch();
    return 0;
}

