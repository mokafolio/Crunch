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
#include <Crunch/LineSegment.hpp>
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
#include <Crunch/TiledFrustum.hpp>
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
    },
    SUITE("RectanglePacker Tests")
    {
        // RectanglePacker packer;
        // packer.setMaxSize(0, 0);
        // packer.reset(5, 5);
        // printf("A\n");
        // EXPECT(!packer.placeRectangle(Rectangle<Float32>(0, 0, 10, 10)));
        // packer.setMaxSize(20, 20);
        // packer.reset(10, 10);
        // EXPECT(packer.placeRectangle(Rectangle<Float32>(0, 0, 10, 10)));
        // EXPECT(packer.placeRectangle(Rectangle<Float32>(0, 0, 10, 10)));
        // EXPECT(packer.placeRectangle(Rectangle<Float32>(0, 0, 10, 10)));
        // EXPECT(packer.placeRectangle(Rectangle<Float32>(0, 0, 5, 5)));
        // EXPECT(packer.placeRectangle(Rectangle<Float32>(0, 0, 5, 5)));
        // EXPECT(packer.placeRectangle(Rectangle<Float32>(0, 0, 10, 5)));
        // EXPECT(!packer.placeRectangle(Rectangle<Float32>(0, 0, 10, 10)));
        // printf("B\n");

        RectanglePacker packer2;
        packer2.reset(1000, 1000);

        Randomizer rand;
        for(int i=0; i<10; ++i)
            EXPECT(packer2.placeRectangle(Rectangle<Float32>(0, 0, rand.randomf(2, 10), rand.randomf(2, 10))));
    },
    SUITE("Line Tests")
    {
        Line2f line(Vec2f(0, 0), Vec2f(1, 0));
        EXPECT(line.position() == Vec2f(0, 0));
        EXPECT(line.direction() == Vec2f(1, 0));

        Line2f line2(Vec2f(50, 0), Vec2f(0, 1));
        auto result = intersect(line, line2);
        EXPECT(result);
        EXPECT(result.intersections().count() == 1);
        EXPECT(result.intersections()[0] == Vec2f(50, 0));

        Line2f line3(Vec2f(-50, 0), Vec2f(0, 1));
        auto result2 = intersect(line, line3);
        EXPECT(result2);
        EXPECT(result2.intersections().count() == 1);
        EXPECT(result2.intersections()[0] == Vec2f(-50, 0));

        Line2f line4(Vec2f(0, 10), Vec2f(1, 0));
        auto result3 = intersect(line, line4);
        EXPECT(!result3);

        //side tests
        auto sideA = line.side(Vec2f(50, -50));
        EXPECT(sideA == 1);
        auto sideB = line.side(Vec2f(50, 50));
        EXPECT(sideB == -1);
        auto sideC = line.side(Vec2f(50, 0));
        EXPECT(sideC == 0);
    },
    SUITE("LineSegment Tests")
    {
        LineSegment2f line(Vec2f(0, 0), Vec2f(100, 0));
        EXPECT(line.positionOne() == Vec2f(0, 0));
        EXPECT(line.positionTwo() == Vec2f(100, 0));

        LineSegment2f line2(Vec2f(50, -50), Vec2f(50, 50));
        auto result = intersect(line, line2);
        EXPECT(result);
        EXPECT(result.intersections().count() == 1);
        EXPECT(result.intersections()[0] == Vec2f(50, 0));

        LineSegment2f line3(Vec2f(-50, -50), Vec2f(-50, 50));
        auto result2 = intersect(line, line3);
        EXPECT(!result2);

        LineSegment2f line4(Vec2f(150, -50), Vec2f(150, 50));
        auto result3 = intersect(line, line4);
        EXPECT(!result3);

        //side tests
        auto sideA = line.side(Vec2f(50, -50));
        EXPECT(sideA == 1);
        auto sideB = line.side(Vec2f(50, 50));
        EXPECT(sideB == -1);
        auto sideC = line.side(Vec2f(50, 0));
        EXPECT(sideC == 0);
        //this is on the extended line (but not between the two provided points)
        auto sideD = line.side(Vec2f(500, 0));
        EXPECT(sideD == 1);
    }
};

int main(int _argc, const char * _args[])
{
    return runTests(spec, _argc, _args);
}
