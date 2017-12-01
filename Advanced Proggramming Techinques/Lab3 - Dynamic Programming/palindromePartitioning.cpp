/*
    ============================================== Info ==============================================

    a[i][j] = true daca str[i..j] formeaza palindrom ,false altfel
    d[i] = numarul minim de taieturi pentru a partitiona str[i..n-1]
    Recurente:
        ==> a[i][j] = true, daca str[i] == str[j] si (j-i < 2 sau a[i+1][j-1] = true)
                    = false, altfel

        ==> d[i] = 0, daca i = n-1
                    d[j+1]+1, daca s[i..j] formeaza palindrom si d[i] > d[j+1]+1
*/

#include <iostream>
#include <string>

using namespace std;

bool a[2000][2000];
int d[2000],p[2000];
string str;
int n;

void computePalindromes()
{
    for(int i = n-1;i>=0;i--)
        a[i][i] = true;

    for(int i = n-1;i>=0;i--)
    {
        d[i] = n-i-1;
        for(int j = i;j<n;j++)
        {
            if(str[i] == str[j] && (a[i+1][j-1] || j-i < 2))
            {
                a[i][j] = true;
                if(j == n-1)
                {
                    d[i] = 0;
                    p[i] = n-1;
                }
                else if(d[i] >= d[j+1]+1)
                {
                    d[i] = d[j+1]+1;
                    p[i] = j;
                }

            }
        }
    }
}

int numberOfPalindromes()
{
    int cnt = 0;
    for(int i = n-1;i>=0;i--)
        for(int j = i;j<n;j++)
          if(i!=j && a[i][j])
            cnt++;
    return cnt;
}

void printPartitions(int i,int j)
{

    for(int k = i;k<=j;k++)
        cout << str[k];
    cout << " ";
    if(j < n-1)
    {
        printPartitions(j+1,p[j+1]);
    }
}

int main()
{
    cin >> str;
    n = str.length();
    computePalindromes();
    cout << "Number of palindromes is: " << numberOfPalindromes() << endl;
    cout << "Palindrome partitioning: ";
    printPartitions(0,p[0]);

    return 0;
}
