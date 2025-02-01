#include <iostream>
#include <pthread.h>
using namespace std;
int flag = 1;
int win = 0;
bool drw = 0;
int matrix[3][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
void print()
{
    cout << endl;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (matrix[i][j] == 1)
            {
                cout << "X"
                     << " ";
            }
            else if (matrix[i][j] == 2)
            {
                cout << "O"
                     << " ";
            }
            else
            {
                cout << i + 1 << j + 1 << " ";
            }
        }
        cout << endl;
    }
    cout << endl;
}
bool draw()
{
    for (size_t i = 0; i < 3; i++)
    {
        for (size_t j = 0; j < 3; j++)
        {
            if (matrix[i][j] == 0)
            {
                return 0;
            }
        }
    }
    return 1;
}
void checkWinner()
{
    for (int i = 0; i < 3; ++i)
    {
        if (matrix[i][0] != 0 && matrix[i][0] == matrix[i][1] && matrix[i][1] == matrix[i][2])
        {
            win = matrix[i][0];
            return;
        }
    }

    for (int j = 0; j < 3; ++j)
    {
        if (matrix[0][j] != 0 && matrix[0][j] == matrix[1][j] && matrix[1][j] == matrix[2][j])
        {
            win = matrix[0][j];
            return;
        }
    }

    if (matrix[0][0] != 0 && matrix[0][0] == matrix[1][1] && matrix[1][1] == matrix[2][2])
    {
        win = matrix[0][0];
        return;
    }
    if (matrix[0][2] != 0 && matrix[0][2] == matrix[1][1] && matrix[1][1] == matrix[2][0])
    {
        win = matrix[0][2];
        return;
    }

    drw = draw();
}

// 1-X
void *player(void *)
{
    int x, y;
    do
    {
        while (flag == 2)
            ;
        // cs
        if (win == 0 && drw == 0)
        {
            cout << "Enter the row" << endl;
            cin >> x;
            cout << "Enter the column" << endl;
            cin >> y;

            if (!((x > 0 && x < 4) && (y > 0 && y < 4)) || matrix[x - 1][y - 1] != 0)
            {
                do
                {
                    cout << "Enter correct row and column" << endl;
                    cout << "Enter the row" << endl;
                    cin >> x;
                    cout << "Enter the column" << endl;
                    cin >> y;
                } while (!((x > 0 && x < 4) && (y > 0 && y < 4)) || matrix[x - 1][y - 1] != 0);
            }

            matrix[x - 1][y - 1] = 1;
            print();
            checkWinner();
        }
        flag = 2;
    } while (!win && !drw);
    pthread_exit(NULL);
}
// 2-O
void *computer(void *)
{
    srand(time(NULL));
    do
    {
        bool f = false;
        int x, y;
        while (flag == 1)
            ;
        // cs
        if (win == 0 && drw == 0)
        {
            x = (rand() % 3) + 1;
            y = (rand() % 3) + 1;
            for (int i = 0; i < 3 && !f; ++i)
            {
                // rows
                if (!f && matrix[i][0] == 1 && matrix[i][1] == 1 && matrix[i][2] == 0)
                {
                    matrix[i][2] = 2;
                    f = true;
                }
                if (!f && matrix[i][0] == 1 && matrix[i][2] == 1 && matrix[i][1] == 0)
                {
                    matrix[i][1] = 2;
                    f = true;
                }
                if (!f && matrix[i][1] == 1 && matrix[i][2] == 1 && matrix[i][0] == 0)
                {
                    matrix[i][0] = 2;
                    f = true;
                }
                //  columns
                if (!f && matrix[0][i] == 1 && matrix[1][i] == 1 && matrix[2][i] == 0)
                {
                    matrix[2][i] = 2;
                    f = true;
                }
                if (!f && matrix[0][i] == 1 && matrix[2][i] == 1 && matrix[1][i] == 0)
                {
                    matrix[1][i] = 2;
                    f = true;
                }
                if (!f && matrix[1][i] == 1 && matrix[2][i] == 1 && matrix[0][i] == 0)
                {
                    matrix[0][i] = 2;
                    f = true;
                }
            }
            //  diagonals
            if (!f && matrix[0][0] == 1 && matrix[1][1] == 1 && matrix[2][2] == 0)
            {
                matrix[2][2] = 2;
                f = true;
            }
            if (!f && matrix[0][0] == 1 && matrix[2][2] == 1 && matrix[1][1] == 0)
            {
                matrix[1][1] = 2;
                f = true;
            }
            if (!f && matrix[1][1] == 1 && matrix[2][2] == 1 && matrix[0][0] == 0)
            {
                matrix[0][0] = 2;
                f = true;
            }
            if (!f && matrix[0][2] == 1 && matrix[1][1] == 1 && matrix[2][0] == 0)
            {
                matrix[2][0] = 2;
                f = true;
            }
            if (!f && matrix[0][2] == 1 && matrix[2][0] == 1 && matrix[1][1] == 0)
            {
                matrix[1][1] = 2;
                f = true;
            }
            if (!f && matrix[1][1] == 1 && matrix[2][0] == 1 && matrix[0][2] == 0)
            {
                matrix[0][2] = 2;
                f = true;
            }

            if (!f)
            {
                do
                {
                    x = (rand() % 3) + 1;
                    y = (rand() % 3) + 1;
                } while (!((x > 0 && x < 4) && (y > 0 && y < 4)) || matrix[x - 1][y - 1] != 0);
                f = true;
                matrix[x - 1][y - 1] = 2;
            }

            // for (size_t i = 0; i < 3 && f; i++)
            // {
            //     for (size_t j = 0; j < 3 && f; j++)
            //     {
            //         if (matrix[i][j] == 0)
            //         {
            //             matrix[i][j] = 2;
            //             f = 0;
            //         }
            //     }
            // }
            print();
            checkWinner();
        }
        flag = 1;
    } while (!win && !drw);
    pthread_exit(NULL);
}
// this one flag method is working because both threads have same condition to exit if it were not the case so one would have stucked if the other thread exits first
int main(int argc, const char **argv)
{
    print();
    pthread_t t1, t2;
    pthread_create(&t1, NULL, &player, NULL);
    pthread_create(&t2, NULL, &computer, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    if (win != 0)
    {
        if (win == 1)
        {
            cout << "Winner is player " << endl;
        }
        else
        {
            cout << "Winner is computer " << endl;
        }
    }
    else
    {
        cout << "It is a draw" << endl;
    }
    return 0;
}
