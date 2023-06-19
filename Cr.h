

#ifndef SNAP_LAB_CR_H
#define SNAP_LAB_CR_H

class Cr
{
protected:
    string classNumber;
    string roomNumber;
    string building;

public:
    Cr(const string classNumber, const string roomNumber, const string building) :
            classNumber(classNumber), roomNumber(roomNumber), building(building){}
    ~Cr() = default;
    string getClassNumber() const {
        return classNumber;
    }

    string getRoomNumber() const {
        return roomNumber;
    }

    string getBuilding() { return building; }
    string toString() const
    {
        return string("cr(") + classNumber + "," + roomNumber + " " + building + string(")");
    }
    friend ostream& operator<< (ostream& os, const Cr& cr)
    {
        return (os << cr.toString());
    }
};

#endif //SNAP_LAB_CR_H
