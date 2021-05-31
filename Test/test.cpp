#include <gtest/gtest.h>
#include <string>

#include "reader.h"

TEST(PulseTest, constructor)
{
    std::string record("         13.               0.40000000      2.                 21.            0.737400      1.      1.   -999.           0.10000000E+01          35               0.66100001");
    Pulse pulse(record);
    EXPECT_EQ(pulse.histNo, 21);
    EXPECT_DOUBLE_EQ(pulse.height, 0.737400);
    EXPECT_EQ(pulse.reaction, 1);
    EXPECT_EQ(pulse.cellNo, 35);
    EXPECT_DOUBLE_EQ(pulse.ergIn, 0.66100001);

    record =           "         22.               0.40000000      2.           89765585.            0.114611      3.      1.   -999.           0.10000000E+01          54               0.11270000";
    pulse = Pulse(record);
    EXPECT_EQ(pulse.histNo, 89765585);
    EXPECT_DOUBLE_EQ(pulse.height, 0.114611);
    EXPECT_EQ(pulse.reaction, 3);
    EXPECT_EQ(pulse.cellNo, 54);
    EXPECT_DOUBLE_EQ(pulse.ergIn, 0.11270000);
}

TEST(EventTest, constructor)
{
    std::string record("        21     1  2    1    55         35   0.228927             0.04     0.84    2.26   -0.16  1.000E+00    0     0    0 6.610E-01");
    Event event(record);
    EXPECT_EQ(event.histNo, 21);
    EXPECT_EQ(event.cellNo, 35);
    EXPECT_DOUBLE_EQ(event.ergDpst, 0.228927);
    Vector3D pos(0.84, 2.26, -0.16);
    EXPECT_DOUBLE_EQ(event.pos.X, pos.X);
    EXPECT_DOUBLE_EQ(event.pos.Y, pos.Y);
    EXPECT_DOUBLE_EQ(event.pos.Z, pos.Z);

    record =          "  99999990     1  2    1    55        604   0.202758             0.04     8.00    1.72   -0.13  1.000E+00    0     0    0 6.610E-01";
    event = Event(record);
    EXPECT_EQ(event.histNo, 99999990);
    EXPECT_EQ(event.cellNo, 604);
    EXPECT_DOUBLE_EQ(event.ergDpst, 0.202758 );
    pos = Vector3D(8.00, 1.72, -0.13);
    EXPECT_DOUBLE_EQ(event.pos.X, pos.X);
    EXPECT_DOUBLE_EQ(event.pos.Y, pos.Y);
    EXPECT_DOUBLE_EQ(event.pos.Z, pos.Z);
}

TEST(ConeTest, constructor)
{
    std::string record("    1.76    2.62   -0.05    0.20   -0.16    0.12  -0.68048645   0.66100001   0.45273100           48");
    Cone cone(record);
    EXPECT_DOUBLE_EQ(cone.apex.X, 1.76);
    EXPECT_DOUBLE_EQ(cone.apex.Y, 2.62);
    EXPECT_DOUBLE_EQ(cone.apex.Z, -0.05);
    EXPECT_DOUBLE_EQ(cone.axis.X, 0.20);
    EXPECT_DOUBLE_EQ(cone.axis.Y, -0.16);
    EXPECT_DOUBLE_EQ(cone.axis.Z, 0.12);
    EXPECT_DOUBLE_EQ(cone.cosHalfAngle, -0.68048645);
    EXPECT_DOUBLE_EQ(cone.E0, 0.66100001);
    EXPECT_DOUBLE_EQ(cone.Edpst, 0.45273100);

    record =           "    1.43    1.43    0.74   -0.59    2.19    0.48   0.97727465   0.66100001   0.01887600          318";
    cone = Cone(record);
    EXPECT_DOUBLE_EQ(cone.apex.X, 1.43);
    EXPECT_DOUBLE_EQ(cone.apex.Y, 1.43);
    EXPECT_DOUBLE_EQ(cone.apex.Z, 0.74);
    EXPECT_DOUBLE_EQ(cone.axis.X, -0.59);
    EXPECT_DOUBLE_EQ(cone.axis.Y, 2.19);
    EXPECT_DOUBLE_EQ(cone.axis.Z, 0.48);
    EXPECT_DOUBLE_EQ(cone.cosHalfAngle, 0.97727465);
    EXPECT_DOUBLE_EQ(cone.E0, 0.66100001);
    EXPECT_DOUBLE_EQ(cone.Edpst, 0.01887600);
}

TEST(getPosTest, getPosTest){
    std::vector<std::string> records = {
        "        48     1  2    1    55         56   0.429851             0.04     1.76    2.62   -0.05  1.000E+00    0     0    0 6.610E-01",
        "        48     1  2    1    55         55   0.073002             0.04     1.95    2.45    0.11  1.000E+00    0     1    0 2.096E-01",
        "        48     1  2    3    55         55   0.105975             0.04     1.96    2.46    0.07  1.000E+00    0     2    0 1.366E-01",
        "        48     1  2    3    55         55   0.030622             0.04     1.97    2.46    0.08  1.000E+00    0     2    0 3.062E-02",
        "        48     3  2    3    55         56   0.013385             0.04     1.76    2.62   -0.05  1.000E+00    0     1    0 1.338E-02",
        "        48     2  2    3    55         56   0.008165             0.04     1.76    2.62   -0.05  1.000E+00    0     1    0 8.165E-03"};
    std::vector<Event> interactions;
    for (int i = 0; i < records.size(); i++)
    {
        interactions.push_back(Event(records[i]));
    }
    Vector3D apex = getPos(interactions, 56);
    EXPECT_DOUBLE_EQ(apex.X, 1.76);
    EXPECT_DOUBLE_EQ(apex.Y, 2.62);
    EXPECT_DOUBLE_EQ(apex.Z, -0.05);

    Vector3D site2 = getPos(interactions, 55);
    EXPECT_DOUBLE_EQ(site2.X, 1.96);
    EXPECT_DOUBLE_EQ(site2.Y, 2.46);
    EXPECT_DOUBLE_EQ(site2.Z, 0.07);
}

TEST(Vector3DTest, operators)
{
    Vector3D v(1,2,3);
    EXPECT_EQ(v*v, 14);
    Vector3D expected(0.1,0.2,0.3);
    Vector3D leftMulti = 0.1 * v;
    EXPECT_DOUBLE_EQ(expected.X, leftMulti.X);
    EXPECT_DOUBLE_EQ(expected.Y, leftMulti.Y);
    EXPECT_DOUBLE_EQ(expected.Z, leftMulti.Z);
    Vector3D rightMulti = v * 0.1;
    EXPECT_DOUBLE_EQ(expected.X, rightMulti.X);
    EXPECT_DOUBLE_EQ(expected.Y, rightMulti.Y);
    EXPECT_DOUBLE_EQ(expected.Z, rightMulti.Z);
    Vector3D division = v / 10;
    EXPECT_DOUBLE_EQ(expected.X, division.X);
    EXPECT_DOUBLE_EQ(expected.Y, division.Y);
    EXPECT_DOUBLE_EQ(expected.Z, division.Z);
}