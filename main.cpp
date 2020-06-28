#include <iostream>
#include <vector>
#include<time.h>
#include <fstream>
#include <assert.h>
#include <string>
#include <cmath>
using namespace std;
class Gauss
{
    vector<vector<double>> A;
    vector<vector<double>> kopia_A;
    int rozmiar;
    vector<double> B;
    vector<double> kopia_B;
    vector<double> X;
    vector<double> pozycja;
public:
    Gauss()
    {
        ifstream source_file;
        source_file.open("dane.csv");
        assert (source_file.is_open());
        source_file >> rozmiar;
        cout << rozmiar << endl;
        for(int j=0;j<rozmiar;j++)
        {
            B.push_back(0);
            X.push_back(0);
            pozycja.push_back(j);
        }
        for (int i = 0 ; i < rozmiar ; i++)
            A.push_back(B);
        char semicolumn;
        for (unsigned i = 0; i < rozmiar+1; i++)
            source_file >> semicolumn;
        for (unsigned i = 0; i < rozmiar; i++)
        {
            for (unsigned j = 0; j < rozmiar; j++)
            {
                source_file >> A[i][j];
                source_file >> semicolumn;
            }
            source_file >> semicolumn;
            source_file >> B[i];
        }
        source_file.close();
        kopia_A = A;
        kopia_B = B;
    }
    void przywroc()
    {
        A = kopia_A;
        B = kopia_B;
    }
    void menu()
    {
        char wybor;
        while(wybor!='0')
        {
            cout << "WYBIERZ OPCJE:\n1. Eliminacja bez wyboru\n2. Eliminacja z wyborem w kolumnie\n3. Eliminacja z wyborem w wierszu\n4. Eliminacja z wyborem pelnym\n0. Zamknij program\n";
            cin >> wybor;
            switch(wybor)
            {
                case '1':
                {
                    this->eliminacja();
                    this->wyswietl();
                    this->wyznaczanie_niewiadomych();
                    this->wyswietl_niewiadome();
                    this->przywroc();
                    break;
                }
                case '2':
                {
                    this->eliminacja_z_kolumnami();
                    this->wyswietl();
                    this->wyznaczanie_niewiadomych();
                    this->wyswietl_niewiadome();
                    this->przywroc();
                    break;
                }
                case '3':
                {
                    this->eliminacja_z_wierszami();
                    this->wyswietl();
                    this->wyznaczanie_niewiadomych();
                    this->wyswietl_niewiadome();
                    this->przywroc();
                    break;
                }
                case '4':
                {
                    this->eliminacja_pelna();
                    this->wyswietl();
                    this->wyznaczanie_niewiadomych();
                    this->wyswietl_niewiadome();
                    this->przywroc();
                    break;
                }
                case '0':
                    cout << "Koniec programu\n";
                    break;
                default:
                    cout << "Wybrano nieznana opcje.\n";
        }
    }
    }
    void eliminacja()
    {
        double p;
        for(int i =0; i < rozmiar; i++)
            for (int w = i+1; w < rozmiar; w++)
            {
                p = A[w][i] / A[i][i];
                B[w] = B[w] - B[i]*p;
                for(int k = i; k < rozmiar; k++)
                {
                    A[w][k] = A[w][k] - A[i][k]*p;
                }
            }

    }
    void eliminacja_z_kolumnami()
    {
        double p;
        for(int i =0; i < rozmiar; i++)
        {
            double maximum = fabs(A[i][i]);
            int index=i;
            for(int l = i+1; l < rozmiar; l++)
            {
                if(maximum < fabs(A[l][i]))
                {
                    maximum = fabs(A[l][i]);
                    index = l;
                }
            }
            A[index].swap(A[i]);
            swap(B[index],B[i]);
            for (int w = i+1; w < rozmiar; w++)
            {
                p = A[w][i] / A[i][i];
                B[w] = B[w] - B[i]*p;
                for(int k = i; k < rozmiar; k++)
                {
                    A[w][k] = A[w][k] - A[i][k]*p;
                }
            }
        }
    }
    void eliminacja_z_wierszami()
    {
        double p;
        for(int i =0; i < rozmiar; i++)
        {
            double maximum = fabs(A[i][i]);
            int index=i;
            for(int l = i+1; l < rozmiar; l++)
            {
                if(maximum < fabs(A[i][l]))
                {
                    maximum = fabs(A[i][l]);
                    index = l;
                }
            }
            for(int l = 0; l < rozmiar; l++)
            {
                swap(A[l][index], A[l][i]);
            }
            swap(pozycja[index], pozycja[i]);
            for (int w = i+1; w < rozmiar; w++)
            {
                p = A[w][i] / A[i][i];
                B[w] = B[w] - B[i]*p;
                for(int k = i; k < rozmiar; k++)
                {
                    A[w][k] = A[w][k] - A[i][k]*p;
                }
            }
        }
    }
    void eliminacja_pelna()
    {
        double p;
        for(int i =0; i < rozmiar; i++)
        {
            double maximum = fabs(A[i][i]);
            int index_wierszy=i;
            int index_kolumn=i;
            for(int l = i; l < rozmiar; l++)
                for(int k = 0; k < rozmiar; k++)
                {
                    if(maximum < fabs(A[l][k]))
                    {
                        maximum = fabs(A[l][k]);
                        index_wierszy = l;
                        index_kolumn = k;
                    }
                }
            for(int l = 0; l < rozmiar; l++)
            {
                swap(A[l][index_kolumn], A[l][i]);
            }
            swap(pozycja[index_kolumn], pozycja[i]);
            A[index_wierszy].swap(A[i]);
            swap(B[index_wierszy],B[i]);
            for (int w = i+1; w < rozmiar; w++)
            {
                p = A[w][i] / A[i][i];
                B[w] = B[w] - B[i]*p;
                for(int k = i; k < rozmiar; k++)
                {
                    A[w][k] = A[w][k] - A[i][k]*p;
                }
            }
        }
    }
    void wyznaczanie_niewiadomych()
    {
        for(int i = rozmiar-1; i >= 0; i--)
        {
            if(i == rozmiar-1) X[i] = B[i] / A[i][i];
            else
            {
                double temp = B[i];
                for(int j = rozmiar-1; j > i; j--) temp -= X[j]*A[i][j];
                X[i] = temp / A[i][i];
            }
        }
    }
    void wyswietl()
    {
        for(int i=0; i<rozmiar; i++)
        {
            for(int j=0; j<rozmiar; j++)
                cout << A[i][j] << "\t";
            cout << B[i] << "\t";
            cout << endl;
        }
        cout << endl;
    }
    void wyswietl_niewiadome()
    {

        for(int i=0; i<rozmiar; i++)
            for(int j=0; j<rozmiar; j++)
            {
                if(i == pozycja[j])
                {
                    swap(pozycja[j],pozycja[i]);
                    swap(X[j],X[i]);
                    break;
                }
            }
        for(int i=0; i<rozmiar; i++)
        {

            cout  << "x" << i << " = " <<  X[i] << "\t" << endl;
        }
        cout << endl;
    }

};

int main()
{

    Gauss m1;
    m1.wyswietl();
    m1.menu();
    return 0;
}
