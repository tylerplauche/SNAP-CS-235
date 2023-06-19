#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define VS_MEM_CHECK _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#else
#define VS_MEM_CHECK
#endif

#ifndef SNAP_LAB_SNAP_H
#define SNAP_LAB_SNAP_H

class Snap
{
private:
    string name;
    string studentId;
    string studentAddress;
    string studentPhone;

public:
    Snap(const string studentId, const string name, const string studentAddress, const string studentPhone) : studentId(studentId), name(name), studentAddress(studentAddress), studentPhone(studentPhone){}
    ~Snap() = default;

    string getName() { return this->name; }
    string getStudentId() { return this->studentId; }
    string getaddress() { return this->studentAddress; }
    string getPhone() { return this->studentPhone; }

    string toString() const
    {
        return string("snap(") + studentId + "," + name + "," + studentAddress + "," + studentPhone + string(")");
    }
    friend ostream& operator << (ostream& os, const Snap& snap)
    {
        return (os << snap.toString());
    }

};

#endif //SNAP_LAB_SNAP_H
