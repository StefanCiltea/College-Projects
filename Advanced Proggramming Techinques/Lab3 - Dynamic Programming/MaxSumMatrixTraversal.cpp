#include <iostream>
#include <fstream>

using namespace std;

void afisRec(int i,int j,int **p)
{
    cout << endl << i << " " << j;
    if(j > 0)
        afisRec(p[i][j],j-1,p);

}

int main()
{
    /* ================== Date ==================*/
    ifstream fin("date.txt");
    int m,n;

    fin >> n >> m;

    int **a,**s,**p;

    a = new int*[n];
    for(size_t i = 0;i<n;i++)
        a[i] = new int[m];

    s = new int*[n];
    for(size_t i = 0;i<n;i++)
        s[i] = new int[m];

    p = new int*[n];
    for(size_t i = 0;i<n;i++)
        p[i] = new int[m];  // p[i][j] = linia pe care se gaseste elementul precedent celui de pe pozitia (i,j)


    for(size_t i = 0;i<n;i++)
        for(size_t j = 0;j<m;j++)
            fin >> a[i][j];

    /* ================== Rezolvare ==================*/

    for(size_t i = 0;i<n;i++) // stim direct
        s[i][0] = a[i][0];

    for(size_t j = 1;j<m;j++)
    {
        for(size_t i = 0;i<n;i++)
        {
            if(i==0)
            {   // ne uitam doar la (i,j-1)
                if(s[i][j-1] > s[i+1][j-1])
                {
                    p[i][j] = i;
                    s[i][j] = s[i][j-1] + a[i][j];
                }
                else
                {
                    p[i][j] = i+1;
                    s[i][j] = s[i+1][j-1] + a[i][j];
                }
            }
            else if(i == n-1)
            {
                // ne uitam doar la (i-1,j-1) si (i,j-1)
                if(s[i][j-1] > s[i-1][j-1])
                {
                    p[i][j] = i;
                    s[i][j] = s[i][j-1] + a[i][j];
                }
                else
                {
                    p[i][j] = i-1;
                    s[i][j] = s[i-1][j-1] + a[i][j];
                }
            }
            else
            {
                // ne uitam la toate cele 3 pozitii

                if(s[i-1][j-1] > s[i][j-1] && s[i-1][j-1] > s[i+1][j-1])
                {
                    // alegem max = (i-1,j-1)
                    p[i][j] = i-1;
                    s[i][j] = s[i-1][j-1] + a[i][j];

                } else if(s[i][j-1] > s[i-1][j-1] && s[i][j-1] > s[i+1][j-1])
                {
                    // alegem max = (i,j-1)
                    p[i][j] = i;
                    s[i][j] = s[i][j-1] + a[i][j];
                }
                else
                {
                    // alegem max = (i+1,j-1)
                    p[i][j] = i+1;
                    s[i][j] = s[i+1][j-1] + a[i][j];
                }
            }
        }
    }

    int sumMax = -1;
    size_t imax;
    for(size_t i = 0;i<n;i++)
        if(s[i][m-1] > sumMax)
        {
            sumMax = s[i][m-1];
            imax = i;
        }
    cout << "Suma maxima este " << sumMax;

    afisRec(imax,m-1,p);
    return 0;
}
