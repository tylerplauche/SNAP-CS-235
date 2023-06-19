//
// Created by Tyler Plauche on 9/25/21.
//

#ifndef SNAP_LAB_CSG_H
#define SNAP_LAB_CSG_H

class Csg
{
protected:
    string classNumber;
    string studentId;
    string grade;

public:
    Csg(const string classNumber, const string studentId, const string grade) :
            classNumber(classNumber), studentId(studentId), grade(grade){}
    ~Csg() = default;

    string getGrade() { return this->grade; }
    string toString() const
    {
        return string("csg(") + classNumber + "," + studentId + "," + grade + string(")");
    }
    const string &getCourseNumber() const {
        return classNumber;
    }
    friend ostream& operator << (ostream& os, const Csg& csg)
    {
        return (os << csg.toString());
    }

    const string &getStudentId() const {
        return studentId;
    }
};


#endif //SNAP_LAB_CSG_H
