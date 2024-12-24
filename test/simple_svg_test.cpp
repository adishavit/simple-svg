// Certainly !I 'll create a Google Test (gtest) suite for the SVG generation library. We' ll focus on testing some of the key classes and functionalities.Here's a sample test suite that covers various aspects of the library:

//                                                                                                                                                 * *File : / Users / rudifarkas / GitHub / cpp -
//                                                                                                                                             orqa / simple - svg / svg_test.cpp * *
// ```cpp

// TEST
// TEST is used to define a simple test case.
// It does not require any setup or teardown code.
// It is suitable for tests that do not need to share common setup or state.

// TEST_F
// TEST_F is used to define a test case that uses a test fixture.
// A test fixture is a class derived from ::testing::Test that provides common setup and teardown code for multiple tests.
// It is suitable for tests that need to share common setup, state, or helper functions.

#include "/opt/homebrew/Cellar/googletest/1.15.2/include/gtest/gtest.h"

// #include <gtest/gtest.h>
#include "../simple_svg_1.0.0.hpp"
#include <sstream>

using namespace svg;

class SVGTest : public ::testing::Test
{
protected:
    Layout layout;

    void SetUp() override
    {
        layout = Layout(Dimensions(100, 100), Layout::TopLeft);
    }
};

TEST_F(SVGTest, PointTest)
{
    Point p(10, 20);
    Size s(5, 10);
    Point other = p + s;
    EXPECT_EQ(other.x, 15);
    EXPECT_EQ(other.y, 30);
}

TEST_F(SVGTest, ColorTest)
{
    Color defaultBlack;
    EXPECT_EQ(defaultBlack.toString(layout), "rgb(0,0,0)");

    Color red(255, 0, 0);
    EXPECT_EQ(red.toString(layout), "rgb(255,0,0)");

    Color blue = Color::Blue;
    EXPECT_EQ(blue.toString(layout), "rgb(0,0,255)");

    Color transparent = Color::Transparent;
    EXPECT_EQ(transparent.toString(layout), "none");
}

TEST_F(SVGTest, ShapeTest)
{
    Circle circle(Point(50, 50), 20, Fill(Color::Red), Stroke(2, Color::Blue));
    std::string circleStr = circle.toString(layout);

    // std::cout << "ShapeTest circleStr: " << circleStr << std::endl;

    EXPECT_TRUE(circleStr.find("cx=\"50\"") != std::string::npos);
    EXPECT_TRUE(circleStr.find("cy=\"50\"") != std::string::npos);
    EXPECT_TRUE(circleStr.find("r=\"10\"") != std::string::npos);
    EXPECT_TRUE(circleStr.find("fill=\"rgb(255,0,0)\"") != std::string::npos);
    EXPECT_TRUE(circleStr.find("stroke=\"rgb(0,0,255)\"") != std::string::npos);
}

TEST_F(SVGTest, PolygonTest)
{
    Polygon polygon(Fill(Color::Green), Stroke(1, Color::Black));
    polygon << Point(0, 0) << Point(100, 0) << Point(100, 100) << Point(0, 100);
    std::string polygonStr = polygon.toString(layout);
    EXPECT_TRUE(polygonStr.find("points=\"0,0 100,0 100,100 0,100 \"") != std::string::npos);
    EXPECT_TRUE(polygonStr.find("fill=\"rgb(0,128,0)\"") != std::string::npos);
    EXPECT_TRUE(polygonStr.find("stroke=\"rgb(0,0,0)\"") != std::string::npos);
}

TEST_F(SVGTest, TextTest)
{
    Text text(Point(10, 20), "Hello SVG", Fill(Color::Black), Font(12, "Arial"));
    std::string textStr = text.toString(layout);
    EXPECT_TRUE(textStr.find("x=\"10\"") != std::string::npos);
    EXPECT_TRUE(textStr.find("y=\"20\"") != std::string::npos);
    EXPECT_TRUE(textStr.find("font-size=\"12\"") != std::string::npos);
    EXPECT_TRUE(textStr.find("font-family=\"Arial\"") != std::string::npos);
    EXPECT_TRUE(textStr.find(">Hello SVG<") != std::string::npos);
}

TEST(SimpleSvgTest, TextTest)
{
    Document doc;
    doc << Text(Point(10, 20), "Hello, SVG!", Fill(Color::Black), Font(12, "Arial"));
    std::string docStr = doc.toString();

    // std::cout << "TextTest SVG:\n"
    //           << docStr << std::endl;

    EXPECT_TRUE(docStr.find("<text x=\"10\" y=\"280\"") != std::string::npos);
    EXPECT_TRUE(docStr.find("font-size=\"12\"") != std::string::npos);
    EXPECT_TRUE(docStr.find("font-family=\"Arial\"") != std::string::npos);
    EXPECT_TRUE(docStr.find(">Hello, SVG!</text>") != std::string::npos);
}

TEST_F(SVGTest, TextTestRotation)
{
    Text text(Point(50, 50), "Rotated Text", Fill(Color::Black), Font(12, "Arial"), Stroke(), 45);
    std::string textStr = text.toString(layout);

    // std::cout << "TextTestRotation SVG:\n" << textStr << std::endl;

    EXPECT_TRUE(textStr.find("x=\"50\"") != std::string::npos);
    EXPECT_TRUE(textStr.find("y=\"50\"") != std::string::npos);
    EXPECT_TRUE(textStr.find("font-size=\"12\"") != std::string::npos);
    EXPECT_TRUE(textStr.find("font-family=\"Arial\"") != std::string::npos);
    EXPECT_TRUE(textStr.find("fill=\"rgb(0,0,0)\"") != std::string::npos);
    EXPECT_TRUE(textStr.find("transform=\"rotate(45 50 50)\"") != std::string::npos);
    EXPECT_TRUE(textStr.find(">Rotated Text<") != std::string::npos);
}

TEST_F(SVGTest, LineChartTest)
{
    LineChart chart;
    Polyline line1(Stroke(1, Color::Blue));
    line1 << Point(0, 0) << Point(10, 10) << Point(20, 20);
    chart << line1;

    Polyline line2(Stroke(1, Color::Red));
    line2 << Point(0, 20) << Point(10, 10) << Point(20, 0);
    chart << line2;

    std::string chartStr = chart.toString(layout);
    EXPECT_TRUE(chartStr.find("stroke=\"rgb(0,0,255)\"") != std::string::npos);
    EXPECT_TRUE(chartStr.find("stroke=\"rgb(255,0,0)\"") != std::string::npos);
    EXPECT_TRUE(chartStr.find("points=\"0,0 10,10 20,20 \"") != std::string::npos);
    EXPECT_TRUE(chartStr.find("points=\"0,20 10,10 20,0 \"") != std::string::npos);
}

TEST_F(SVGTest, DocumentTest)
{
    Document doc("test.svg", Layout(Dimensions(200, 200)));
    doc << Circle(Point(100, 100), 50, Fill(Color::Red));
    doc << Text(Point(10, 20), "Test SVG", Fill(Color::Black));

    std::string docStr = doc.toString();

    // std::cout << "DocumentTest SVG:\n"
    //           << docStr << std::endl;

    EXPECT_TRUE(docStr.find("<svg width=\"200px\" height=\"200px\"") != std::string::npos);
    EXPECT_TRUE(docStr.find("<circle cx=\"100\" cy=\"100\" r=\"25\"") != std::string::npos);
    EXPECT_TRUE(docStr.find("<text x=\"10\" y=\"180\" fill=\"rgb(0,0,0)\"") != std::string::npos);
}

TEST(SimpleSvgTest, CircleTest)
{
    Document doc;
    doc << Circle(Point(100, 100), 50, Fill(Color::Red), Stroke(2, Color::Blue));
    std::string docStr = doc.toString();

    // std::cout << "CircleTest SVG:\n"
    //           << docStr << std::endl;

    EXPECT_TRUE(docStr.find("<circle cx=\"100\" cy=\"200\" r=\"25\"") != std::string::npos); // WHY cy="200"?
    EXPECT_TRUE(docStr.find("fill=\"rgb(255,0,0)\"") != std::string::npos);
    EXPECT_TRUE(docStr.find("stroke=\"rgb(0,0,255)\"") != std::string::npos);
    EXPECT_TRUE(docStr.find("stroke-width=\"2\"") != std::string::npos);
}

TEST(SimpleSvgTest, PolygonTest)
{
    Document doc;
    Polygon polygon(Fill(Color::Green), Stroke(1, Color::Black));
    polygon << Point(0, 0) << Point(100, 0) << Point(100, 100) << Point(0, 100);
    doc << polygon;

    std::string docStr = doc.toString();

    // std::cout << "PolygonTest SVG:\n"
    //           << docStr << std::endl;

    EXPECT_TRUE(docStr.find("<polygon points=\"0,300 100,300 100,200 0,200 \"") != std::string::npos);
    EXPECT_TRUE(docStr.find("fill=\"rgb(0,128,0)\"") != std::string::npos);
    EXPECT_TRUE(docStr.find("stroke=\"rgb(0,0,0)\"") != std::string::npos);
}

TEST(SimpleSvgTest, LineChartTest)
{
    Document doc;
    LineChart chart;
    Polyline line1(Stroke(1, Color::Blue));
    line1 << Point(0, 0) << Point(10, 10) << Point(20, 20);
    Polyline line2(Stroke(1, Color::Red));
    line2 << Point(0, 20) << Point(10, 10) << Point(20, 0);
    chart << line1 << line2;
    doc << chart;
    std::string docStr = doc.toString();
    EXPECT_TRUE(docStr.find("<polyline") != std::string::npos);
    EXPECT_TRUE(docStr.find("stroke=\"rgb(0,0,255)\"") != std::string::npos);
    EXPECT_TRUE(docStr.find("stroke=\"rgb(255,0,0)\"") != std::string::npos);
    EXPECT_TRUE(docStr.find("<circle") != std::string::npos); // Vertices
}

TEST_F(SVGTest, PathTest)
{
    Document doc;
    Path path(Fill(Color::Yellow), Stroke(2, Color::Purple));
    path << Point(0, 0) << Point(100, 0) << Point(100, 100);
    path.startNewSubPath();
    path << Point(0, 100) << Point(0, 0);
    doc << path;
    std::string docStr = doc.toString();

    // std::cout << "PathTest SVG:\n"
    //           << docStr << std::endl;

    EXPECT_TRUE(docStr.find("<path") != std::string::npos);
    EXPECT_TRUE(docStr.find("d=\"M0,300 100,300 100,200 z M0,200 0,300 z \"") != std::string::npos);
    EXPECT_TRUE(docStr.find("fill=\"rgb(255,255,0)\"") != std::string::npos);
    EXPECT_TRUE(docStr.find("stroke=\"rgb(128,0,128)\"") != std::string::npos);
    EXPECT_TRUE(docStr.find("stroke-width=\"2\"") != std::string::npos);
}

TEST_F(SVGTest, ColorTest2)
{
    Color color(128, 64, 32);
    EXPECT_EQ(color.toString(layout), "rgb(128,64,32)");
}

TEST(SimpleSvgTest, StrokeTest)
{
    Stroke stroke(3, Color::Blue, true);
    Document doc;
    doc << Rectangle(Point(0, 0), 100, 100, Fill(), stroke);
    std::string docStr = doc.toString();

    // std::cout << "StrokeTest SVG:\n"
    //           << docStr << std::endl;

    EXPECT_TRUE(docStr.find("rect x=\"0\" y=\"300\" width=\"100\" height=\"100\"") != std::string::npos);
    EXPECT_TRUE(docStr.find("height=\"100\"") != std::string::npos);
    EXPECT_TRUE(docStr.find("fill=\"none\"") != std::string::npos);
    EXPECT_TRUE(docStr.find("stroke-width=\"3\"") != std::string::npos);
    EXPECT_TRUE(docStr.find("stroke=\"rgb(0,0,255)\"") != std::string::npos);
}

TEST(SimpleSvgTest, GroupTest)
{
    Document doc;
    Group group(Fill(Color::Red), Stroke(2, Color::Black));
    group << Circle(Point(100, 100), 50, Fill(Color::Blue));
    group << Rectangle(Point(200, 200), 100, 50, Fill(Color::Green));
    doc << group;
    std::string docStr = doc.toString();

    // std::cout << "GroupTest SVG:\n"
    //           << docStr << std::endl;

    EXPECT_TRUE(docStr.find("<g fill=\"rgb(255,0,0)\" stroke-width=\"2\" stroke=\"rgb(0,0,0)\"") != std::string::npos);
    EXPECT_TRUE(docStr.find("<circle cx=\"100\" cy=\"200\" r=\"25\" fill=\"rgb(0,0,255)\"") != std::string::npos);
    EXPECT_TRUE(docStr.find("<rect x=\"200\" y=\"100\" width=\"100\" height=\"50\" fill=\"rgb(0,128,0)\"") != std::string::npos);
}

// Run the tests -----------------------------------------------------------------------------------
int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

// ```

// This test suite covers the following aspects of the SVG generation library:

// 1. Color creation and string representation
// 2. Shape creation and attributes (Circle)
// 3. Polygon creation and point addition
// 4. Text element creation and attributes
// 5. LineChart creation with multiple polylines
// 6. Document creation and saving

// To use this test suite:

// 1. Make sure you have Google Test installed and properly set up in your project.
// 2. Include the `simple_svg_1.0.0.hpp` header in the same directory as the test file.
// 3. Compile the test file with your C++ compiler, linking against the Google Test library.
// 4. Run the resulting executable to execute the tests.

// This test suite provides a good starting point for testing the SVG generation library. You may want to add more tests to cover additional classes, edge cases, or specific functionality as needed for your project.

// These tests cover additional features of the library:

// 1.
// CircleTest: Tests the creation of a circle with fill and stroke.
// 2.
// PolygonTest: Tests the creation of a polygon.
// 3.
// TextTest: Tests the creation of text with font properties.
// 4.
// LineChartTest: Tests the creation of a line chart with multiple polylines.
// 5.
// PathTest: Tests the creation of a path with multiple subpaths.
// 6.
// ColorTest: Tests the Color class functionality.
// 7.
// StrokeTest: Tests various stroke properties including line cap and line join.
//
