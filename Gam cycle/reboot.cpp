#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int **matrix;
int *min_way;      // мин путь
int *save_way;     // для вывода
int length = 1000; // очень большая длина пути
int sum_length = 0;
bool *mark;                     // посещенные
string mf_name = "matrix2.txt"; // файл с матрицей

void get_matrix(int &n)
{
    ifstream mfin(mf_name);
    mfin >> n;
    matrix = new int *[n];
    for (int i = 0; i < n; i++)
    {
        matrix[i] = new int[n];
        for (int j = 0; j < n; j++)
            mfin >> matrix[i][j];
    }
    mfin.close();

    mark = new bool[n];
    min_way = new int[n];
    save_way = new int[n + 1];

    for (int i = 0; i < n; i++)
    {
        mark[i] = 0;
        min_way[i] = -1;
        save_way[i] = -1;
    }
    save_way[n] = -1;
}

// рекурсия поиска мин цикла
void dfs(int &v, int &w, int &n, int k)
{
    mark[v] = 1;
    min_way[k] = v;
    if (v == w)
    {
        if (sum_length < length && min_way[n - 1] != -1 && matrix[min_way[0]][min_way[n - 1]] != 0)
        {
            length = sum_length;
            for (int i = 0; i < n; i++)
                save_way[i] = min_way[i];
            save_way[n] = save_way[0];
        }
    }
    else
        for (int j = 0; j < n; j++)
            if (matrix[v][j] != 0 && mark[j] == 0)
            {
                sum_length += matrix[v][j];
                dfs(j, w, n, k + 1);
                sum_length -= matrix[v][j];
            }
    min_way[k] = -1;
    mark[v] = 0;
}

int main()
{
    system("cls");
    int n;
    get_matrix(n);
    int w = 2; // какая-то вершина
    int k = 0;
    for (int i = 0; i < n; i++)
    {
        sum_length = 0;
        for (int j = 0; j < n; j++)
            min_way[j] = -1;
        dfs(i, w, n, k);
    }

    for (int i = 0; i < n + 1; i++)
        cout << save_way[i] << endl;
}