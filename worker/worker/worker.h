#pragma once
#include <iostream>
#include <fstream>
using namespace std;

class worker
{
private:
    char name[50];
    char role[50];
    int ICS;
public:
    worker();
    worker(const char*, const char*, int);
    worker(const worker& w);
    ~worker();
    int getICS();
    const char* getName() const { return name; }  
    bool operator>(const worker& b);
    worker& operator=(const worker& b);
    friend ostream& operator<<(ostream& os, const worker& w)
    {
        return os << w.name << " " << w.role << " " << w.ICS;
    }
    friend istream& operator>>(istream& is, worker& w)
    {
        return is >> w.name >> w.role >> w.ICS;
    }
};
