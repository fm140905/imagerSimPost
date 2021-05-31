#pragma once

#include <sstream>
#include <string>
#include <vector>
#include <cmath>

class Vector3D
{
public:
    double X=0;
    double Y=0;
    double Z=0;
    Vector3D():Vector3D(0, 0, 0) {}
    Vector3D(const double x, const double y, const double z): X(x), Y(y), Z(z) {}

    Vector3D operator+(const Vector3D& r) const {
        return Vector3D(this->X + r.X, this->Y + r.Y, this->Z + r.Z);
    }
    Vector3D operator-(const Vector3D& r) const {
        return Vector3D(this->X - r.X, this->Y - r.Y, this->Z - r.Z);
    }

    double operator*(const Vector3D& r) const {
        return this->X * r.X + this->Y * r.Y + this->Z * r.Z;
    }
    Vector3D operator*(const double& d) const {
        return Vector3D(this->X * d,  this->Y * d, this->Z * d);
    }
    Vector3D operator/(const double& d) const {
        return Vector3D(this->X / d,  this->Y / d, this->Z / d);
    }
};

inline Vector3D operator*(const double& d, const Vector3D& r){
    return r * d;
}

inline double getCosAngle(const Vector3D& l, const Vector3D& r) {
    return l*r / std::sqrt((l*l) * (r*r));
}

class Cone
{
public:
    // interaction site 1 is the apex
    Vector3D apex;
    // site 2 - site 1 is the axis
    Vector3D axis;
    // half angle = abs (scattering angle)
    // for neutron, 0 < half angle < pi /2
    // for gamma,   0 < half angle < pi
    double cosHalfAngle;
    // initial energy
    double E0;
    // energy deposited in compoton scattering
    double Edpst;
    Cone(): Cone(Vector3D(0,0,0), Vector3D(0,0,0), 0, 0, 0) {}
    Cone(const Vector3D point, const Vector3D line, const double cosTheta, const double E0_, const double Edpst_): 
       apex(point), axis(line), cosHalfAngle(cosTheta), E0(E0_), Edpst(Edpst_) {}
    Cone(const std::string& record) {
        apex = Vector3D(std::stod(record.substr(0, 8)), 
                        std::stod(record.substr(8, 8)), 
                        std::stod(record.substr(16, 8)));
        axis = Vector3D(std::stod(record.substr(24, 8)), 
                        std::stod(record.substr(32, 8)), 
                        std::stod(record.substr(40, 8)));
        cosHalfAngle = std::stod(record.substr(48, 13));
        E0 = std::stod(record.substr(61, 13));
        Edpst = std::stod(record.substr(74, 13));
    }
};


class Pulse
{
private:
    /* data */
public:
    ulong histNo=0; // history number
    double height=0; // pulse amplitude, MeV
    ushort reaction=0; // reaction type, 1 or 3
    int cellNo=0; // cell number
    double ergIn=0; // energy of incoming photon, MeV
    Pulse() {}
    Pulse(std::string record) {
        histNo = std::stoi(record.substr(56, 8));
        height = std::stod(record.substr(77, 9));
        reaction = std::stoi(record.substr(88, 4));
        cellNo = std::stoi(record.substr(137, 9));
        ergIn = std::stod(record.substr(161, 10));
    }
};

class Event
{
private:
    /* data */
public:
    ulong histNo=0; // history number
    int cellNo=0; // cell number
    double ergDpst=0; // energy of incoming photon, MeV
    Vector3D pos=Vector3D(0,0,0);
    Event() {}
    Event(std::string record) {
        histNo = std::stoi(record.substr(0, 10));
        cellNo = std::stoi(record.substr(35, 6));
        ergDpst = std::stod(record.substr(44, 8));
        pos = Vector3D(stod(record.substr(72,6)),
                       stod(record.substr(80,6)),
                       stod(record.substr(88,6)));
    }
};

Vector3D getPos(const std::vector<Event>& events, const int& cellNo);