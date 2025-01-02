
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

ShapeColl createSVGElements() {
    std::cout << "Creating SVG elements..." << std::endl;

    ShapeColl elements;

    // Long notation
    LineChart chart(Dimensions(12.5, 12.5));
    Polyline polyline_a(Stroke(1.25, Color::Blue));
    Polyline polyline_b(Stroke(1.25, Color::Aqua));
    Polyline polyline_c(Stroke(1.25, Color::Fuchsia));
    polyline_a << Point(0, 0) << Point(25, 75)
        << Point(50, 100) << Point(75, 112.5) << Point(100, 110);
    polyline_b << Point(0, 25) << Point(25, 55)
        << Point(50, 75) << Point(75, 80) << Point(100, 75);
    polyline_c << Point(0, 30) << Point(25, 37.5)
        << Point(50, 35) << Point(75, 25) << Point(100, 5);
    chart << polyline_a << polyline_b << polyline_c;
    elements << chart;

    // Condensed notation
    elements << (LineChart(Dimensions(162.5, 12.5))
        << (Polyline(Stroke(1.25, Color::Blue)) << Point(0, 0) << Point(25, 20) << Point(50, 32.5))
        << (Polyline(Stroke(1.25, Color::Orange)) << Point(0, 25) << Point(25, 40) << Point(50, 50))
        << (Polyline(Stroke(1.25, Color::Cyan)) << Point(0, 12.5) << Point(25, 32.5) << Point(50, 40)));

    elements << Circle(Point(200, 200), 50, Fill(Color(100, 200, 120)), Stroke(2.5, Color(200, 250, 150)));

    elements << Text(Point(12.5, 192.5), "Simple SVG", Fill(Color::Silver), Font(25, "Verdana"));

    elements << (Polygon(Fill(Color(200, 160, 220)), Stroke(1.25, Color(150, 160, 200))) << Point(50, 175)
        << Point(62.5, 180) << Point(82.5, 175) << Point(87.5, 150) << Point(62.5, 137.5) << Point(45, 157.5));

    elements << Rectangle(Point(175, 137.5), 50, 37.5, Fill(Color::Yellow), Stroke(1, Color::Black));

    std::cout << "SVG elements created successfully." << std::endl;
    return elements;
}

// Demo page shows sample usage of the Simple SVG library.


int main()
{
    try
    {
        std::cout << "Starting main function..." << std::endl;

        std::string filename = "my_svg.svg";
        Dimensions dimensions(500, 500);

        std::cout << "Creating Document..." << std::endl;
        Document doc(filename, Layout(dimensions, Layout::BottomLeft));

        std::cout << "Creating border..." << std::endl;
        Polygon border(Stroke(1, Color::Red));
        border << Point(0, 0) << Point(dimensions.width, 0)
               << Point(dimensions.width, dimensions.height) << Point(0, dimensions.height);

        std::cout << "Adding border to document..." << std::endl;
        doc << border;

        std::cout << "Creating SVG elements..." << std::endl;
        ShapeColl elements = createSVGElements();

        std::cout << "Adding elements to document..." << std::endl;
        doc << elements;

        std::cout << "Saving document..." << std::endl;
        if (doc.save())
        {
            std::cout << "File saved successfully: " << filename << std::endl;
        }
        else
        {
            std::cout << "Failed to save the file: " << filename << std::endl;
        }

        std::cout << "Main function completed successfully." << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << "An exception occurred: " << e.what() << std::endl;
    }
    catch (...)
    {
        std::cerr << "An unknown exception occurred." << std::endl;
    }

    return 0;
}
