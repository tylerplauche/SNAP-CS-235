#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "snap.h"
#include "Cr.h"
#include "Csg.h"

using namespace std;

#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define VS_MEM_CHECK _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#else
#define VS_MEM_CHECK
#endif


#ifndef SNAP_LAB_CDH_H
#define SNAP_LAB_CDH_H
class Cdh
{
protected:
    string classNumber;
    string day;
    string time;

public:
    Cdh(const string classNumber, const string day, const string time) : classNumber(classNumber), day(day), time(time){}
    ~Cdh() = default;
    string getClassNumber() const {
        return classNumber;
    }
    string getDay() { return this->day; }
    string getTime() { return this->time; }

    string toString() const
    {
        return string("cdh(") + classNumber + "," + day + "," + time + string(")");
    }
    friend ostream& operator << (ostream& os, const Cdh& cdh)
    {
        return (os << cdh.toString());
    }


};

#endif //SNAP_LAB_CDH_H
