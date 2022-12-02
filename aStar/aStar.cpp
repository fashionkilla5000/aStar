// aStar.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>

using namespace std;

static int wymX = 19;
static int wymY = 19;

static int startX = 0;
static int startY = 0;
static int celX = 19;
static int celY = 19;

struct obiekt {
    int pozX = 0;
    int pozY = 0;
    int rodzX = 0;
    int rodzY = 0;
    int g = 0;
    float f = 0;
};

bool czyPoza(int x, int y)
{
    if (x < 0 || x > wymX || y < 0 || y > wymY)
        return true;  
    return false;
}
bool czyPrzeszkoda(double** G, int x, int y)
{
    if (G[x+1][y+1] == 5)
        return true; 
    return false;
}
bool czyCel(int obecnyX, int obecnyY, int celX, int celY)
{
    if (obecnyX == celX && obecnyY == celY)
        return true; 
    return false;
}
bool czyZawiera(vector<obiekt> zamknieta, int x, int y) {
    obiekt pomoc;
    for (vector<obiekt>::iterator it = zamknieta.begin(); it != zamknieta.end(); ++it)
    {
        pomoc = *it;
        if (pomoc.pozX == x && pomoc.pozY == y)
            return true;
    }
    return false;
}
float heurystyka(int obecnyX, int obecnyY, int celX, int celY)
{
    float H = sqrt((pow((obecnyX - celX),2) + pow((obecnyY - celY),2)));
    return H;
}
obiekt ustawianieWartosci(obiekt Grid[19][19], int x, int y , int rodzicX, int rodzicY, int g, float f)
{
    Grid[x][y].pozX = x;
    Grid[x][y].pozY = y;
    Grid[x][y].rodzX = rodzicX;
    Grid[x][y].rodzY = rodzicY;
    Grid[x][y].g = g;
    Grid[x][y].f = f; 
    return Grid[x][y];
}
void stworzDroge(double** G, vector<obiekt> zamknieta) {
    
    vector<obiekt>::iterator i = zamknieta.end();

    bool koniec = false;
    obiekt pom;
    obiekt pom2;
    pom = zamknieta.back();
    G[pom.pozX+1][pom.pozY+1] = 3;

    while (koniec == false)
    {
        pom2 = zamknieta.back();
        if (pom.rodzX == pom2.pozX && pom.rodzY == pom2.pozY)
        {
            G[pom.pozX+1][pom.pozY+1] = 3;
            pom = pom2;
        }
        if (pom2.pozX == startX && pom2.pozY == startY)
        {
            G[pom.pozX+1][pom.pozY+1] = 3;
            getchar();
            cout << "\nWypisujemy na ekran\n\n";
            for (int i = 1; i < wymX+2; i++)
            {
                for (int j = 1; j < wymY+2; j++)
                {
                    cout << " " << G[j][i];
                }cout << "\n";
            }
            getchar();
            exit(0);
            koniec = true;
        }
        zamknieta.pop_back();
    }

}


void aGwiazdka(double** G, int celX, int celY)
{
    int kierunki[] = { 0,1,0,-1,-1,0,1,0 };
    int g = 0;
    float f = 0;
    float pom = FLT_MAX;
    int obecnyX = startX;
    int obecnyY = startY;
    vector <obiekt> otwarta;
    vector <obiekt> zamknieta;

    obiekt Grid[19][19]; 
    for (int i = 0; i < 19; i++)
    {
        for (int j = 0; j < 19; j++) 
        {
            Grid[i][j] = ustawianieWartosci(Grid, i, j, -1, -1, 0, 0);
        }
    }
    Grid[obecnyX][obecnyY] = ustawianieWartosci(Grid, obecnyX, obecnyY, 0, 0, 0, 0);
    
    zamknieta.push_back(Grid[obecnyX][obecnyY]);

    bool cel = false;
    
    int x = 0;
    int y = 0;
    while (cel!=true)
    {
        f = 0;
        pom = FLT_MAX;
        for (int i = 0; i < 8; i += 2)
        {
            x = obecnyX + kierunki[i];
            y = obecnyY + kierunki[i + 1];

            if (czyPoza(x, y) == false)
                if (czyPrzeszkoda(G, x, y) == false)
                {
                    if (czyZawiera(zamknieta, x, y) == false)
                    {
                        if (czyZawiera(otwarta, x, y) == false) {
                            if (czyCel(x, y, celX, celY) == true) {
                                getchar();
                                cout << "Znaleziono droge!" << endl;
                                stworzDroge(G, zamknieta);
                                cel = true;
                                getchar();
                            }
                            Grid[x][y].g = Grid[obecnyX][obecnyY].g + 1;
                            g = Grid[x][y].g;
                            f = g + heurystyka(x, y, celX, celY);
                            Grid[x][y] = ustawianieWartosci(Grid, x, y, obecnyX, obecnyY, g, f);
                            otwarta.push_back(Grid[x][y]);

                        }
                    }
                }
        }
        if (otwarta.size() == 0 && cel == false) {
            cout << "Nie znaleziono trasy :(" << endl;
            exit(0);
        }
        obiekt pomO;
        vector<obiekt>::iterator iPomO;
        for (vector<obiekt>::iterator i = otwarta.begin(); i != otwarta.end(); ++i)
        {
            pomO = *i;
            if (pomO.f < pom)
            {
                pom = pomO.f;
                iPomO = i;
            }
        }

        pomO = *iPomO;

        otwarta.erase(iPomO);
        zamknieta.push_back(pomO);

        obecnyX = pomO.pozX;
        obecnyY = pomO.pozY;
    }

}


int main(void) {

    cout << "Wczytywanie danych z pliku\n";

    string nazwap = "grid.txt";
    int wym2 = 20;
    int wym1 = 20;

    //teraz deklarujemy dynamicznie tablice do, której wczytamyu nasz plik,
    int rows = wym2 + 1;
    double** G;
    G = new double* [rows];
    while (rows--) G[rows] = new double[wym1 + 1];

    cout << "\n\nNacisnij ENTER aby wczytac tablice o nazwie " << nazwap;
    getchar();

    std::ifstream plik(nazwap.c_str());

    for (unsigned int i = 1; i < wym2 + 1; i++)
    {
        for (unsigned int j = 1; j < wym1 + 1; j++)
        {
            plik >> G[j][i];
        }
    }
    plik.close();

    cout << "\nWypisujemy na ekran\n\n";
    for (int i = 1; i < wym2 + 1; i++)
    {
        for (int j = 1; j < wym1 + 1; j++)
        {
            cout << " " << G[j][i];
        }cout << "\n";
    }

    G[celX+1][celY+1] = 3;

    aGwiazdka(G, celX, celY);

    cout << "\nWypisujemy na ekran\n\n";
    for (int i = 1; i < wym2 + 1; i++)
    {
        for (int j = 1; j < wym1 + 1; j++)
        {
            cout << " " << G[i][j];
        }cout << "\n";
    }

    //na koniec czyścimy pamięć po naszej tablicy
    for (int i = 0; i < wym2 + 1; i++)
    {
        delete[] G[i];
    }//czyscimy wiersze
    delete[] G;//zwalniamy tablice wskaznikow do wierszy

    cout << "\n\nNacisnij ENTER aby zakonczyc";
    getchar();

    return 0;
}