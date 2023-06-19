#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include "snap.h"
#include "Csgdhr.h"
#include "Cr.h"
#include "Csg.h"
#include "Cdh.h"
using namespace std;

#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define VS_MEM_CHECK _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#else
#define VS_MEM_CHECK
#endif

vector<Csgdhr> join(vector<Cdh> cdhs, vector<Csg> csgs, vector<Cr> crs) {
    vector<Csgdhr> csgdhrs;
    for(Cdh cdh: cdhs) {
        for(Csg csg: csgs) {
            for(Cr cr : crs) {
                if((cdh.getClassNumber() == csg.getCourseNumber()) && (cdh.getClassNumber() == cr.getClassNumber())) {
                    Csgdhr csgdhr(csg.getCourseNumber(), csg.getStudentId(), csg.getGrade(),
                                  cdh.getDay(), cdh.getTime(),cr. getRoomNumber(),
                                  cr.getBuilding());
                    csgdhrs.push_back(csgdhr);
                }
            }
        }
    }
    return csgdhrs;
}
bool contains(vector<Csgdhr> list, Csgdhr candidate) {
    for(Csgdhr csgdhr : list) {
        if(candidate.getCourseNumber() == csgdhr.getCourseNumber()) {
            return true;
        }
    }
    return false;
}
int main(int argc, char *argv[]) {
    VS_MEM_CHECK

    if (argc < 3)
    {
        cerr << "Please provide name of input and output files";
        return 1;
    }
    cout << "Input file: " << argv[1] << endl;
    ifstream in(argv[1]);
    if (!in)
    {
        cerr << "Unable to open " << argv[1] << " for input";
        return 2;
    }
    cout << "Output file: " << argv[2] << endl;
    ofstream out(argv[2]);
    //out.open(argv[2]);
    if (!out)
    {
        in.close();
        cerr << "Unable to open " << argv[2] << " for output";
        return 3;
    }

    out << "Input Strings:";
    vector<Snap> snap;
    vector<Csg> csg;
    vector<Cdh> cdh;
    vector<Cr> cr;
    map<string, string> studentNames;
    map<string, vector<Csgdhr>> studentSchedules;
    map<string, string> courseDays;

    for (string line; getline(in,line);)
    {
        try {
            if ("snap(" == line.substr(0, 5)) {
                out << endl << line;
                string studentId = line.substr(5, line.find(',') - 5);
                line = line.substr(line.find(',') + 1);
                string studentName = line.substr(0, line.find(','));
                line = line.substr(line.find(',') + 1);
                string studentAddress = line.substr(0, line.find(','));
                line = line.substr(line.find(',') + 1);
                string studentNumber = line.substr(0, line.find(')'));
                snap.push_back(Snap(studentId, studentName, studentAddress, studentNumber));
                studentNames[studentId] = studentName;
                //cout << endl << studentNumber << endl;
            }
            else if ("csg(" == line.substr(0, 4))
            {
                out << endl << line;
                string classNumber = line.substr(4, line.find(',') - 4);
                line = line.substr(line.find(',') + 1);
                string studentId = line.substr(0, line.find(','));
                line = line.substr(line.find(',') + 1);
                string grade = line.substr(0, line.find(')'));
                csg.push_back(Csg(classNumber, studentId, grade));
            }
            else if ("cdh(" == line.substr(0, 4))
            {
                out << endl << line;
                string classNumber = line.substr(4, line.find(',') - 4);
                line = line.substr(line.find(',') + 1);
                string day = line.substr(0, line.find(','));
                courseDays[classNumber] += day;
                line = line.substr(line.find(',') + 1);
                string time = line.substr(0, line.find(')'));
                cdh.push_back(Cdh(classNumber, day, time));

            }
            else if ("cr(" == line.substr(0, 3))
            {
                out << endl << line;
                string classNumber = line.substr(3, line.find(',') - 3);
                line = line.substr(line.find(',') + 1);
                string roomNumber = line.substr(0, line.find(' '));
                line = line.substr(line.find(' ') + 1);
                string building = line.substr(0, line.find(')'));
                cr.push_back(Cr(classNumber, roomNumber, building));


            }
            else {
                out << endl << "**Error: " << line;
                throw string("**what???");
            }
        }


        catch (const string& s) {cerr << "something " << s;}
        catch(...) {
            cerr << "idk ";
        }
    }
    in.close();

    out << endl << endl << "Vectors:";
    for (size_t i = 0; i < snap.size(); i++) out << endl << snap[i];
    for (size_t i = 0; i < csg.size(); i++) out << endl << csg[i];
    for (size_t i = 0; i < cdh.size(); i++) out << endl << cdh[i];
    for (size_t i = 0; i < cr.size(); i++) out << endl << cr[i];

    out << endl << endl << "Course Grades:";
    string courseName = csg[0].getCourseNumber();
    for (size_t i = 0; i < csg.size(); i++)
    {
        if(csg[i].getCourseNumber() != courseName) {
            out << endl;
        }
        courseName = csg[i].getCourseNumber();
        out << endl << csg[i].getCourseNumber() << ",";
        out << studentNames[csg[i].getStudentId()] << ",";
        out << csg[i].getGrade();
    }

    vector<Csgdhr> csgdhrs = join(cdh, csg, cr);

    for(Csgdhr csgdhr : csgdhrs) {
        if(!contains(studentSchedules[csgdhr.getStudentID()], csgdhr)) {
            studentSchedules[csgdhr.getStudentID()].push_back(csgdhr);
        }
    }

    out << endl << endl << "Student Schedules:";
    for (size_t i = 0; i < snap.size(); i++)
    {
        out << endl << snap[i].getName()<< ", ";
        out << snap[i].getStudentId() << ", ";
        out << snap[i].getaddress() << ", ";
        out << snap[i].getPhone() << endl;
        vector<Csgdhr> schedules = studentSchedules[snap[i].getStudentId()];
        for(Csgdhr schedule : schedules) {
            out << "  " << schedule.getCourseNumber() << " ";
            out << courseDays[schedule.getCourseNumber()] << " ";
            out << schedule.getTime() << ", ";
            out << schedule.getLocation() << " " << endl;

            //out << courseDays[cdh[i].getCourseNumber()];
        }
        //out << cdh[i].getCourseNumber() << " ";
        //out << courseDays[cdh[i].getCourseNumber()];
        /*for (size_t i = 0; i < cdh.size(); i++)
        {
            out << cdh[i].getDay();
        }*/
        //out << " " << cdh[i].getTime() << ", ";
        //out << cr[0].getBuilding() << endl;

    }






    return 0;
}

