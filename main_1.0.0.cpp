
/*******************************************************************************
*  The "New BSD License" : http://www.opensource.org/licenses/bsd-license.php  *
********************************************************************************

Copyright (c) 2010, Mark Turney
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the <organization> nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

******************************************************************************/

#include "simple_svg_1.0.0.hpp"

using namespace svg;

// Demo page shows sample usage of the Simple SVG library.

void demo1()
{
    const std::string filename = "my_svg.svg";
    Dimensions dimensions(500, 500);
    Document doc(filename, Layout(dimensions, Layout::BottomLeft));

    // Red image border.
    Polygon border(Stroke(5, Color(Color::Red)));
    border << Point(0, 0) << Point(dimensions.width, 0)
           << Point(dimensions.width, dimensions.height) << Point(0, dimensions.height);
    doc << border;

    // Long notation.  Local variable is created, children are added to varaible.
    LineChart chart(Dimensions(), 25.0, Stroke(0.5, Color(Color::Purple)));
    Polyline polyline_a(Stroke(3.0, Color(Color::Blue)));
    Polyline polyline_b(Stroke(3.0, Color(Color::Aqua)));
    Polyline polyline_c(Stroke(3.0, Color(Color::Fuchsia)));
    polyline_a << Point(0, 0) << Point(50, 150)
               << Point(100, 200) << Point(150, 225) << Point(200, 220);
    polyline_b << Point(0, 50) << Point(50, 110)
               << Point(100, 150) << Point(150, 160) << Point(200, 150);
    polyline_c << Point(0, 60) << Point(50, 75)
               << Point(100, 70) << Point(150, 50) << Point(200, 10);
    chart << polyline_a << polyline_b << polyline_c;
    doc << chart;

    // Condensed notation, parenthesis isolate temporaries that are inserted into parents.
    doc << (LineChart(Dimensions(325, 25))
            << (Polyline(Stroke(2.5, Color(Color::Blue))) << Point(0, 0) << Point(50, 40) << Point(100, 65))
            << (Polyline(Stroke(2.5, Color(Color::Orange))) << Point(0, 50) << Point(50, 80) << Point(100, 100))
            << (Polyline(Stroke(2.5, Color(Color::Cyan))) << Point(0, 25) << Point(50, 65) << Point(100, 80)));

    doc << Circle(Point(400, 400), 100, Fill(Color(100, 200, 120)), Stroke(5, Color(200, 250, 150)));

    doc << Text(Point(25, 385), "Simple SVG", Fill(Color::Silver), Font(50, "Verdana"));

    doc << (Polygon(Fill(Color(200, 160, 220)), Stroke(2.5, Color(150, 160, 200)))
            << Point(100, 350) << Point(125, 360) << Point(165, 350)
            << Point(175, 300) << Point(125, 275) << Point(90, 315));

    Rectangle rect(Point(350, 275), 100, 75, Fill(Color::Yellow));
    rect.setRotation(60);
    doc << rect;

    Group myGroup(Fill(Color::Red), Stroke(2, Color(Color::Black)));
    myGroup << Circle(Point(100, 100), 50, Fill(Color::Blue))
            << Rectangle(Point(200, 200), 100, 50, Fill(Color::Green));

    Text text(Point(0, 0), "Hello world!", Fill(Color::Black), Font(10, "Verdana"), Stroke(), 90);

    myGroup << text;

    text.setRotation(-5); // Rotate the text 45 degrees
    myGroup << text;      // Add the text to the group

    doc << myGroup;

    doc.save();

    std::cout << "SVG saved to: " << filename << std::endl;

    system(("open " + filename).c_str()); // Open the file in the default browser
}

void demo2()
{
    const std::string filename = "my.svg";
    Dimensions dimensions(200, 200);

    // Use TopLeft layout so that (0, 0) is the top left corner of the SVG
    // but specify coordinates in user space (origin at bottom left, +y axis upwards)
    Document doc(filename, Layout(dimensions, Layout::TopLeft));

    Rectangle rect1(Point(0, 0), 100, 100, Fill(), Stroke(1.0, Color(Color::Blue)));
    doc << rect1;

    Rectangle rect2(Point(100, 100), 100, 100, Fill(), Stroke(1.0, Color(Color::Red)));
    doc << rect2;

    {
        Text text(Point(0, 0), "Hello world!", Fill(Color::Black), Font(10, "Verdana"), Stroke(), 90);
        doc << text;
        text.setRotation(45);
        doc << text;
    }
    {
        Text text(Point(100, 100), "Hello world!", Fill(Color::Black), Font(10, "Verdana"), Stroke(), 90);
        doc << text;
        text.setRotation(45);
        doc << text;
    }

    doc.save();

    std::cout << "SVG saved to: " << filename << std::endl;

    system(("open " + filename).c_str()); // Open the file in the default browser
}

int main() // Example usage of the Simple SVG library.
{
    demo1();
    demo2();

    return 0;
}
