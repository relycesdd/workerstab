#include "worker.h"
#include <cstring>

worker::worker()
{
    name[0] = '\0';
    role[0] = '\0';
    ICS = 0;
}
worker::worker(const char* n, const char* r, int y)
{
    strcpy_s(name, 50, n);
    strcpy_s(role, 50, r);
    ICS = y;
}
worker::worker(const worker& w)
{
    strcpy_s(name, w.name);
    strcpy_s(role, w.role);
    ICS = w.ICS;
}
worker::~worker()
{
}

int worker::getICS()
{
    return ICS;
}
bool worker::operator>(const worker& b)
{
    return strcmp(this->name, b.name) > 0;
}
worker& worker::operator=(const worker& b)
{
    strcpy_s(name, b.name);
    strcpy_s(role, b.role);
    ICS = b.ICS;
    return *this;
}