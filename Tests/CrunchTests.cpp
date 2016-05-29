#include <Crunch/Bezier.hpp>
#include <Crunch/Circle.hpp>
#include <Crunch/Color1.hpp>
#include <Crunch/Color3.hpp>
#include <Crunch/Color4.hpp>
#include <Crunch/Colors.hpp>
#include <Crunch/CommonFunc.hpp>
#include <Crunch/Constants.hpp>
#include <Crunch/GeometricFunc.hpp>
#include <Crunch/Line.hpp>
#include <Crunch/Matrix2.hpp>
#include <Crunch/Matrix3.hpp>
#include <Crunch/Matrix4.hpp>
#include <Crunch/MatrixFunc.hpp>
#include <Crunch/NumericalFunc.hpp>
#include <Crunch/PerlinNoise.hpp>
#include <Crunch/Quaternion.hpp>
#include <Crunch/QuaternionFunc.hpp>
#include <Crunch/Randomizer.hpp>
#include <Crunch/Rectangle.hpp>
#include <Crunch/RectanglePacker.hpp>
#include <Crunch/StringConversion.hpp>
#include <Crunch/TrigonometryFunc.hpp>
#include <Crunch/Tween.hpp>
#include <Crunch/UtilityFunc.hpp>
#include <Crunch/Vector2.hpp>
#include <Crunch/Vector3.hpp>
#include <Crunch/Vector4.hpp>
#include <Stick/Test.hpp>

using namespace stick;
using namespace crunch;

const Suite spec[] =
{
    SUITE("Vector Tests")
    {
    },
    SUITE("Color Tests")
    {
        ColorRGB col(1.0f, 0.5f, 0.1f);
        EXPECT(col.r == 1.0f);
        EXPECT(col.g == 0.5f);
        EXPECT(col.b == 0.1f);

        ColorRGBA col2 = toRGBA(col);
        EXPECT(col2.r == 1.0f);
        EXPECT(col2.g == 0.5f);
        EXPECT(col2.b == 0.1f);
        EXPECT(col2.a == 1.0f);

        ColorHSB col3 = toHSB(ColorRGB(0.0f, 0.0f, 1.0f));
        EXPECT(isClose(col3.h, 0.666667f, 0.000001f));
        EXPECT(col3.s == 1.0f);
        EXPECT(col3.b == 1.0f);

        ColorRGBA col4 = toRGBA(col3);
        EXPECT(col4.r == 0.0f);
        EXPECT(col4.g == 0.0f);
        EXPECT(col4.b == 1.0f);
        EXPECT(col4.a == 1.0f);
    },
    SUITE("Tween Tests")
    {
        TweenCubicEaseOutf tween(0, 1, 2.0);
        Float32 result = tween.update(2.0);
        EXPECT(result ==  1.0);
        EXPECT(tween.isFinished());

        TweenLinearEaseOutf tween2(0, 1, 2.0);
        result = tween2.update(2.0);
        EXPECT(result ==  1.0);
        EXPECT(tween2.isFinished());
    }
};

int main(int _argc, const char * _args[])
{
    return runTests(spec, _argc, _args);
}
