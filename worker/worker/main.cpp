#define CRT_SECURE_NO_WARNING
#include <iostream>
#include <fstream>
#include <cstring>
#include "worker.h"

using namespace std;

void insertionSort(worker a[], int n) // {11 1 12 2} {1 11 12 2}
{
    for (int i = 1; i < n; i++) //i=2 i=3
    {
        worker key = a[i]; // {1} {12} {2}
        int j = i - 1; // 0 1 2

        while (j >= 0 && a[j] > key) // 11 > 1 11 > 12 12 > 2 11 > 2 1 > 2
        {
            a[j + 1] = a[j]; // {11 11 12 2} {1 11 12 2} {1 11 12 12} {1 11 11 12}
            j = j - 1; // j=-1 j= 1 j=1 j=0
        }

        a[j + 1] = key; // {1 11 12 2} {1 11 12 2} {1 2 11 12}
    }
}

void selectionSort(worker a[], int n) // {11 1 12 2} {1 11 12 2} {1 2 12 11}
{
    for (int i = 0; i < n - 1; i++) //i=0 i=1 i=2
    {
        int minIndex = i; //minIndex=0 minIndex=1 minIndex=2

        for (int j = i + 1; j < n; j++) //j=1 //j=2 j=3 j=2 j=3 j=3
        {
            if (a[minIndex] > a[j]) //11>1 !1>12 !1>2 !11>12 11>2 12>11
            {
                minIndex = j; //minIndex= 1 minIndex=3 minIndex=3
            }
        }
        swap(a[i], a[minIndex]); //{1 11 12 2} {1 2 12 11} {1 2 11 12}
    }
}

void bubbleSort(worker a[], int n) // {11 1 12 2} {1 11 12 2}
{
    for (int i = 0; i < n - 1; i++) //i=0 i=1 i=2
    {
        for (int j = 0; j < n - i - 1; j++) //j=0 j=1 j=2 j=0 j=1
        {
            if (a[j] > a[j + 1]) //11>1 !11>12 12>2 !1>11 11>2
            {
                swap(a[j], a[j + 1]); //{1 11 12 2} {1 11 2 12} {1 2 11 12} 
            }
        }
    }
}

void shellSort(worker a[], int n) //{11 1 12 2 13 3 14 4}
{
    for (int gap = n / 2; gap > 0; gap = gap / 2) //gap=4 gap=2 gap=1
    {
        for (int i = gap; i < n; i++) //i=4 i=5 i=2 i=1 i=2
        {
            worker temp = a[i]; //temp = 13 temp=3 temp=12 temp=1 temp =12
            int j = i; //j=4 j=5 j=2 j=1 j=2

            while (j >= gap && a[j - gap] > temp) // !11>13 !1 > 3(skip till gap/2(2)) 
            {
                a[j] = a[j - gap]; //{11 11 12 2 13 3 14 4}
                j = j - gap; //j=0
            }

            a[j] = temp; //{1 11 12 2 13 3 14 4}
        }
    }
}

int partition(worker a[], int low, int high) //{11 1 12 2 13 3 14 4} {1 11 12 2 13 3 14 4}
{
    worker pivot = a[high]; //pivot={4} pivot={4}
    int i = low - 1; //i=-1  i=-1

    for (int j = low; j < high; j++)//j=0 j=1 j=2 j=3 j=4 j=5 j=6 j=0 j=1
    {
        if (pivot > a[j]) //!4>11 4>1 !4>12 4>2 !4>13 4>3 !4>14 4>1
        {
            i++; //i=0 i=1 i=2 i=0
            swap(a[i], a[j]); //{1 11 12 2 13 3 14 4} {1 2 12 11 13 3 14 4} {1 11 3 2 13 12 14 4} {}
        }
    }

    swap(a[i + 1], a[high]); //{1 11 4 2 13 12 14 3}

    return i + 1; //i=3
}

void quickSort(worker a[], int low, int high)
{
    if (low < high) //1<3
    {
        int p = partition(a, low, high); //low=1 high=3

        quickSort(a, low, p - 1); //0 2 {1 11 4}
        quickSort(a, p + 1, high);// 4 7 {13 12 14 3}
    }
}

int compareWorker(const void* x, const void* y)
{
    worker* a = (worker*)x;
    worker* b = (worker*)y;

    if (*a > *b)
        return 1;

    if (*b > *a)
        return -1;

    return 0;
}


/////////////////////////////////


const int m = 23;

int hashTable[m][2];  

void initHashTable() 
{
    for (int i = 0; i < m; i++) 
    {
        hashTable[i][0] = -1;
        hashTable[i][1] = -1;
    }
}

int hashFunc(int key, int i) {
    return (key + i * i) % m;
}

int getKey(const char* name) {
    int sum = 0;
    int len = 0;
    for (int i = 0; name[i] != '\0'; i++) {
        sum += (unsigned char)name[i];
        len++;
    }
    if (len == 0) return 0;
    return sum / len;
}

void createHashTable(worker* arr, int n) {
    initHashTable();
    for (int i = 0; i < n; i++) {
        int key = getKey(arr[i].getName());
        int j, ii = 0;
        while (1) {
            j = hashFunc(key, ii);
            if (hashTable[j][1] == -1) break;
            ii++;
        }
        hashTable[j][0] = key;
        hashTable[j][1] = i;
    }
}

int searchHash(int key) {
    int ii = 0, j;
    while (ii < m) {
        j = hashFunc(key, ii);
        if (hashTable[j][1] == -1) return -1;
        if (hashTable[j][0] == key) return hashTable[j][1];
        ii++;
    }
    return -1;
}

int main()
{
    worker workers[10];

    ifstream fin("worker.txt");

    if (!fin)
    {
        cout << "file not found\n";
        return 0;
    }

    for (int i = 0; i < 10; i++)
    {
        fin >> workers[i];
    }

    fin.close();

    cout << "Original workers:\n";

    for (int i = 0; i < 10; i++)
    {
        cout << workers[i] << endl;
    }

    insertionSort(workers, 10);

    cout << "\nSorted workers:\n";

    for (int i = 0; i < 10; i++)
    {
        cout << workers[i] << endl;
    }

    ofstream fout("worker.bin", ios::binary);
    for (int i = 0; i < 10; i++)
    {
        fout.write((char*)&workers[i], sizeof(worker));
    }
    fout.close();

    createHashTable(workers, 10);

    cout << "\n=== HASH TABLE ===\n";
    for (int i = 0; i < m; i++) {
        cout << i << ": key=" << hashTable[i][0]
            << " index=" << hashTable[i][1];
        if (hashTable[i][1] != -1) {
            cout << " -> " << workers[hashTable[i][1]];
        }
        cout << endl;
    }
    cout << "==================\n";

    char searchName[50];
    cout << "\nEnter name for hash search: ";
    cin >> searchName;

    int searchKey = getKey(searchName);
    int recordNum = searchHash(searchKey);

    if (recordNum != -1) {
        cout << "Found in hash table, record #" << recordNum << endl;
        ifstream finBin("worker.bin", ios::binary);
        finBin.seekg(recordNum * sizeof(worker), ios::beg);

        worker found;
        finBin.read((char*)&found, sizeof(worker));
        finBin.close();

        cout << "Data from binary file: " << found << endl;
    }
    else {
        cout << "Not found in hash table\n";
    }


    worker w2[10];

    ifstream fin2("worker.bin", ios::binary);

    for (int i = 0; i < 10; i++)
    {
        fin2.read((char*)&w2[i], sizeof(worker));
    }

    fin2.close();

    int exp;

    cout << "\nEnter work experience: ";
    cin >> exp;

    int NowIs = 2026;

    bool found = false;

    cout << "\nWorkers with experience more than "
        << exp << ":\n";

    for (int i = 0; i < 10; i++)
    {
        int experience = NowIs - w2[i].getICS();

        if (experience > exp)
        {
            cout << w2[i] << endl;
            found = true;
        }
    }

    if (!found)
    {
        cout << "No workers found\n";
    }

    return 0;
}