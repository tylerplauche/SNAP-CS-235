#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "Cdh.h"
using namespace std;

#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define VS_MEM_CHECK _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#else
#define VS_MEM_CHECK
#endif

#ifndef SNAP_LAB_COURSE_H
#define SNAP_LAB_COURSE_H

class Csgdhr : public Csg, Cdh, Cr {


public:
    Csgdhr(string course, string studentID, string grade, string day, string hour, string room, string building)
    : Csg(course, studentID, grade ), Cdh(course, day,hour),
    Cr(course, room, building){}

    string getStudentID() { return studentId; }
    string getTime() { return time; }
    string getLocation() { return roomNumber + " " + building; }

};


#endif //SNAP_LAB_COURSE_H
