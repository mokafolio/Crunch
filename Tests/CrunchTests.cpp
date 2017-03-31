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
        for (int i = 0; i < 10; ++i)
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
    },
    SUITE("Bezier Classification Tests")
    {
        BezierCubic2f point(Vec2f(100, 100), Vec2f(100, 100), Vec2f(100, 100), Vec2f(100, 100));
        BezierCubic2f line(Vec2f(100, 100), Vec2f(100, 100), Vec2f(200, 200), Vec2f(200, 200));
        BezierCubic2f cusp(Vec2f(100, 200), Vec2f(200, 100), Vec2f(100, 100), Vec2f(200, 200));
        BezierCubic2f loop(Vec2f(100, 200), Vec2f(250, 100), Vec2f(50, 100), Vec2f(200, 200));
        BezierCubic2f single(Vec2f(100, 100), Vec2f(150, 100), Vec2f(173, 154), Vec2f(200, 200));
        BezierCubic2f doublee(Vec2f(100, 200), Vec2f(200, 100), Vec2f(160, 120), Vec2f(200, 200));
        BezierCubic2f arch(Vec2f(100, 100), Vec2f(150, 100), Vec2f(200, 150), Vec2f(200, 200));

        auto a = point.classify();
        EXPECT(a.type == CurveType::Line);
        EXPECT(a.roots.count == 0);

        auto b = line.classify();
        EXPECT(b.type == CurveType::Line);
        EXPECT(b.roots.count == 0);

        auto c = cusp.classify();
        EXPECT(c.type == CurveType::Cusp);
        EXPECT(c.roots.count == 1);
        EXPECT(isClose(c.roots.values[0], 0.5f));

        auto d = loop.classify();
        EXPECT(d.type == CurveType::Loop);
        EXPECT(d.roots.count == 2);
        EXPECT(isClose(d.roots.values[0], 0.17267316464601132f));
        EXPECT(isClose(d.roots.values[1], 0.8273268353539888f));

        auto e = single.classify();
        EXPECT(e.type == CurveType::Serpentine);
        EXPECT(e.roots.count == 1);
        EXPECT(isClose(e.roots.values[0], 0.870967741935484f));

        auto f = doublee.classify();
        EXPECT(f.type == CurveType::Serpentine);
        EXPECT(f.roots.count == 2);
        EXPECT(isClose(f.roots.values[0], 0.15047207654837885f));
        EXPECT(isClose(f.roots.values[1], 0.7384168123405099f));

        auto g = arch.classify();
        EXPECT(g.type == CurveType::Arch);
        EXPECT(g.roots.count == 0);
    },
    SUITE("Bezier::parameterOf Tests")
    {
        BezierCubic2f loop(Vec2f(100, 200), Vec2f(250, 100), Vec2f(50, 100), Vec2f(200, 200));

        for (Float32 i = 0.0f; i <= 1.0f; i += 0.1f)
        {
            auto p1 = loop.positionAt(i);
            auto param = loop.parameterOf(p1);
            printf("PARAM %f %f\n", i, param);
            EXPECT(isClose(param, i, 1E-6f));
        }

        auto param = loop.parameterOf(Vec2f(0, 0));
        EXPECT(param == -1);
    },
    SUITE("Bezier::overlaps Tests")
    {
        BezierCubic2f loop(Vec2f(100, 200), Vec2f(250, 100), Vec2f(50, 100), Vec2f(200, 200));
        BezierCubic2f loop2(loop);
        auto result = loop.overlaps(loop2);
        EXPECT(result.count);
        EXPECT(result.count == 2);
        EXPECT(isClose(result.values[0].parameterOne, 0.0f));
        EXPECT(isClose(result.values[0].parameterTwo, 0.0f));
        EXPECT(isClose(result.values[1].parameterOne, 1.0f));
        EXPECT(isClose(result.values[1].parameterTwo, 1.0f));

        BezierCubic2f loop3 = loop.slice(0.25, 0.75);
        auto result2 = loop.overlaps(loop3);
        EXPECT(result2.count);
        EXPECT(result2.count == 2);
        EXPECT(isClose(result2.values[0].parameterOne, 0.25f, BezierCubic2f::epsilon));
        EXPECT(isClose(result2.values[0].parameterTwo, 0.0f, BezierCubic2f::epsilon));
        EXPECT(isClose(result2.values[1].parameterOne, 0.75f, BezierCubic2f::epsilon));
        EXPECT(isClose(result2.values[1].parameterTwo, 1.0f, BezierCubic2f::epsilon));
    },
    SUITE("Bezier::intersections Tests")
    {
        // test the straight case
        BezierCubic2f a(Vec2f(100, 100), Vec2f(100, 100), Vec2f(300, 100), Vec2f(300, 100));
        BezierCubic2f b(Vec2f(200, 50), Vec2f(200, 50), Vec2f(200, 150), Vec2f(200, 150));
        auto res = a.intersections(b);
        EXPECT(res.count == 1);
        EXPECT(isClose(res.values[0].parameterOne, 0.5f, BezierCubic2f::curveTimeEpsilon));
        EXPECT(isClose(res.values[0].parameterTwo, 0.5f, BezierCubic2f::curveTimeEpsilon));
        EXPECT(isClose(a.positionAt(res.values[0].parameterOne), Vec2f(200, 100), BezierCubic2f::geometricEpsilon));
        EXPECT(isClose(b.positionAt(res.values[0].parameterTwo), Vec2f(200, 100), BezierCubic2f::geometricEpsilon));
        EXPECT(isClose(res.values[0].position, Vec2f(200, 100), BezierCubic2f::geometricEpsilon));

        // test the first curve / line case
        BezierCubic2f c(Vec2f(190, 60), Vec2f(250, 60), Vec2f(250, 140), Vec2f(190, 140));
        BezierCubic2f d(Vec2f(200, 50), Vec2f(200, 50), Vec2f(200, 150), Vec2f(200, 150));
        auto res2 = c.intersections(d);
        EXPECT(res2.count == 2);
        EXPECT(isClose(res2.values[0].parameterOne, 0.05904f, BezierCubic2f::curveTimeEpsilon));
        EXPECT(isClose(res2.values[1].parameterOne, 0.94096f, BezierCubic2f::curveTimeEpsilon));
        EXPECT(isClose(res2.values[0].position, Vec2f(200, 60.80368), BezierCubic2f::geometricEpsilon));
        EXPECT(isClose(res2.values[1].position, Vec2f(200, 139.19632), BezierCubic2f::geometricEpsilon));
        printf("%f %f %f %f\n", res2.values[0].parameterOne, res2.values[0].parameterTwo,
               res2.values[1].parameterOne, res2.values[1].parameterTwo);
        //EXPECT(isClose(res.values[0], Vec2f(200, 100), BezierCubic2f::geometricEpsilon));
    }
};

int main(int _argc, const char * _args[])
{
    return runTests(spec, _argc, _args);
}
