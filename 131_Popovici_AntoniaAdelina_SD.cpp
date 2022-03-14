// DE CITIT FISIERUL README!!!

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
using namespace std;
ifstream fin("TextFile1.txt");

void GenerateNumbers(long long* v, long long a, long long b, long long n)
{
    long long i;
    for (i = 0; i < n; i++)
        v[i] = rand() % (b + 1 - a) + a;
}

void CountingSort(long long* v, long long n)
{
    long long i, j;
    long long* b = new long long[n];
    long long* c = new long long[n];

    for (i = 0; i < n; i++)
    {
        b[i] = 0;
        c[i] = 0;
    }

    for (i = 0; i < n; i++)
        c[i] = v[i];
    for (i = 1; i < n; i++)
        for (j = 0; j < i; j++)
            if (c[j] < c[i])
                b[i]++;
            else
                b[j]++;
    for (i = 0; i < n; i++)
        v[b[i]] = c[i];

    delete[] b;
    delete[] c;
}

void InsertionSort(long long* v, long long n)
{
    for (int i = 1; i < n; i++)
    {
        long long x = v[i];
        int aux = i - 1;
        while (aux >= 0
            && v[aux] > x)
        {
            v[aux + 1] = v[aux];
            aux--;
        }
        v[aux + 1] = x;
    }
}

void Merge(long long* v, long long* c, long long mid, long long left, long long right)
{
    long long i, j, k;
    k = 0;
    i = left;
    j = mid + 1;
    while (i <= mid && j <= right)
    {
        if (v[i] <= v[j])
            c[k++] = v[i++];
        else
            c[k++] = v[j++];
    }

    while (i <= mid)
        c[k++] = v[i++];

    while (j <= right)
        c[k++] = v[j++];

    for (i = left, j = 0; i <= right; i++, j++)
        v[i] = c[j];
}

void MergeSort(long long* v, long long* c, long long left, long long right)
{
    if (right > left)
    {
        long long mid = (left + right) / 2;
        MergeSort(v, c, left, mid);
        MergeSort(v, c, mid + 1, right);
        Merge(v, c, mid, left, right);
    }
}

void ShellSort(long long* v, long long n)
{
    long long i, j, k;
    i = n / 2;
    while (i >= 1)
    {
        for (j = i; j < n; j++)
        {
            for (k = j - i; k >= 0; k = k - i)
            {
                if (v[k + i] >= v[k])
                    break;
                else
                    swap(v[k + i], v[k]);
            }
        }
        i /= 2;
    }
}

void FindMax(long long& maxim, long long* v, long long n)
{
    long long i;
    for (i = 0; i < n; i++)
        if (v[i] > maxim)
            maxim = v[i];
}

void CountSort(long long* v, long long n, long long x)
{
    long long i;
    long long* vecAux = new long long[n];
    long long* countV = new long long[n];
    long long pas = 1;
    x--;
    for (i = 0; i < n; i++)
    {
        countV[i] = 0;
        vecAux[i] = 0;
    }
    while (x > 0)
    {
        pas *= 10;
        x--;
    }
    for (i = 0; i < n; i++)
        countV[(v[i] / pas) % 10]++;

    for (i = 1; i < 10; i++)
        countV[i] += countV[i - 1];

    for (i = n - 1; i >= 0; i--)
    {
        vecAux[countV[(v[i] / pas) % 10] - 1] = v[i];
        countV[(v[i] / pas) % 10]--;
    }
    for (i = 0; i < n; i++)
        v[i] = vecAux[i];

    delete[] vecAux;
    delete[] countV;
}

void RadixSort(long long* v, long long n)
{
    long long maxim = v[0];
    FindMax(maxim, v, n);
    long long nrOfDig = 0;
    while (maxim > 0)
    {
        maxim /= 10;
        nrOfDig++;
    }
    long long i;
    for (i = 1; i <= nrOfDig; i++)
        CountSort(v, n, i);
}

bool VerificareSortare(long long* v, int n)
{
    int i;
    for (i = 1; i < n; i++)
        if (v[i] < v[i - 1])
            return false;
    return true;
}
long long* v;

int main()
{
    int N[10];
    long long Max[10];

    int i, T;
    fin >> T;
    for (i = 0; i < T; i++)
    {
        fin >> N[i];
        fin >> Max[i];
    }

    srand((unsigned)time(NULL));
    for (i = 0; i < T; i++)
    {
        cout << "Test " << i + 1 << ":" << endl;
        cout << endl;
        v = new long long[N[i]];
        clock_t t1, t2;
        cout << "> N = " << N[i] << ", Max = " << Max[i] << '\n' << '\n';

        GenerateNumbers(v, 0, Max[i], N[i]);
        t1 = clock();
        RadixSort(v, N[i]);
        t2 = clock();
        double timp = ((double)t2 - t1) / CLOCKS_PER_SEC;
        cout << "Radix Sort: timp = " << timp << ", sortat corect = " << VerificareSortare(v, N[i]) << '\n';

        GenerateNumbers(v, 0, Max[i], N[i]);
        t1 = clock();
        ShellSort(v, N[i]);
        t2 = clock();
        timp = ((double)t2 - t1) / CLOCKS_PER_SEC;
        cout << "Shell Sort: timp = " << timp << ", sortat corect = " << VerificareSortare(v, N[i]) << '\n';

        GenerateNumbers(v, 0, Max[i], N[i]);
        t1 = clock();
        long long* c = new long long[N[i]];
        MergeSort(v, c, 0, (long long)N[i] - 1);
        t2 = clock();
        timp = ((double)t2 - t1) / CLOCKS_PER_SEC;
        cout << "Merge Sort: timp = " << timp << ", sortat corect = " << VerificareSortare(v, N[i]) << '\n';
        delete[] c;
        c = nullptr;
        
        if (N[i] < 1000000)
        {
            GenerateNumbers(v, 0, Max[i], N[i]);
            t1 = clock();
            CountingSort(v, N[i]);
            t2 = clock();
            timp = ((double)t2 - t1) / CLOCKS_PER_SEC;
            cout << "Counting Sort: timp = " << timp << ", sortat corect = " << VerificareSortare(v, N[i]) << '\n';
        }
        else
            cout << "Counting Sort: timpul de sortare este prea mare (aproximativ 2 ore)" << '\n';

        if (N[i] < 1000000)
        {
            GenerateNumbers(v, 0, Max[i], N[i]);
            t1 = clock();
            InsertionSort(v, N[i]);
            t2 = clock();
            timp = ((double)t2 - t1) / CLOCKS_PER_SEC;
            cout << "Insertion Sort: timp = " << timp << ", sortat corect = " << VerificareSortare(v, N[i]) << '\n';
        }
        else
            cout << "Insertion Sort: timpul de sortare este prea mare (aproximativ 30 de minute)" << '\n';
        GenerateNumbers(v, 0, Max[i], N[i]);
        t1 = clock();
        sort(v, v + N[i]);
        t2 = clock();
        timp = ((double)t2 - t1) / CLOCKS_PER_SEC;
        cout << "Sortare nativa a limbajului: timp = " << timp << ", sortat corect = " << VerificareSortare(v, N[i]) << '\n' << '\n';

        delete[] v;
    }
    return 0;
}
