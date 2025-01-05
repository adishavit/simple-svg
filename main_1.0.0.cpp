
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

ShapeColl createSVGElements()
{
    ShapeColl elements;

    // Create a LineChart with Long notation
    LineChart chart(Dimensions(12.5, 12.5));

    // Create three Polylines with different colors and strokes
    Polyline polyline_a(Stroke(1.25, Color::Blue));
    Polyline polyline_b(Stroke(1.25, Color::Aqua));
    Polyline polyline_c(Stroke(1.25, Color::Fuchsia));

    // Add points to each polyline
    polyline_a << Point(0, 0) << Point(25, 75) << Point(50, 100)
               << Point(75, 112.5) << Point(100, 110);
    polyline_b << Point(0, 25) << Point(25, 55) << Point(50, 75)
               << Point(75, 80) << Point(100, 75);
    polyline_c << Point(0, 30) << Point(25, 37.5) << Point(50, 35)
               << Point(75, 25) << Point(100, 5);

    // Add the polylines to the chart
    chart << polyline_a << polyline_b << polyline_c;

    // Add the chart to the elements collection
    elements << chart;

    // Create and add another LineChart with Condensed notation
    elements << (LineChart(Dimensions(162.5, 12.5))
                 << (Polyline(Stroke(1.25, Color::Blue))
                     << Point(0, 0) << Point(25, 20) << Point(50, 32.5))
                 << (Polyline(Stroke(1.25, Color::Orange))
                     << Point(0, 25) << Point(25, 40) << Point(50, 50))
                 << (Polyline(Stroke(1.25, Color::Cyan))
                     << Point(0, 12.5) << Point(25, 32.5) << Point(50, 40)));

    // Create and add a Circle with specific properties
    elements << Circle(Point(200, 200), 50, Fill(Color(100, 200, 120)),
                       Stroke(2.5, Color(200, 250, 150)));

    // Create and add a Text element with specific properties
    auto text = Text(Point(12.5, 192.5), "Simple SVG", Fill(Color::Silver),
                     Font(25, "Verdana"));
    elements << text;

    // Create and add a Rectangle to represent the Text bounding box
    auto bb = text.getBoundingBox();
    elements << Rectangle(bb.origin, bb.size.width, bb.size.height,
                          Fill(Color::Transparent), Stroke(1, Color::Red));

    // Create and add a Polygon with specific properties
    elements << (Polygon(Fill(Color(200, 160, 220)),
                         Stroke(1.25, Color(150, 160, 200)))
                 << Point(50, 175) << Point(62.5, 180) << Point(82.5, 175)
                 << Point(87.5, 150) << Point(62.5, 137.5) << Point(45, 157.5));

    // Create and add a Rectangle with specific properties
    elements << Rectangle(Point(175, 137.5), 50, 37.5, Fill(Color::Yellow),
                          Stroke(1, Color::Black));

    // Create an ellipse with specific properties
    elements << Elipse(Point(200, 120), 50, 25, Fill(Color::Red),
                       Stroke(1.5, Color::Black));

    // Return the collection of SVG elements
    return elements;
}

// Demo page shows sample usage of the Simple SVG library.

void demoDocLayout(const Layout &layout)
{
    // Generate filename based on the layout origin type
    std::string filename;
    switch (layout.origin)
    {
        case Layout::TopLeft:
            filename = "svg_topleft.svg";
            break;
        case Layout::TopRight:
            filename = "svg_topright.svg";
            break;
        case Layout::BottomLeft:
            filename = "svg_bottomleft.svg";
            break;
        case Layout::BottomRight:
            filename = "svg_bottomright.svg";
            break;
    }

    // Create SVG document with specified layout
    Document doc(filename, layout);

    // Draw border rectangle using document dimensions
    Polygon border(Stroke(1, Color::Red));
    border << Point(0, 0) << Point(layout.dimensions.width, 0)
           << Point(layout.dimensions.width, layout.dimensions.height)
           << Point(0, layout.dimensions.height);
    doc << border;

    // Mark origin and the farthest point in the layout with circles
    doc << Circle(Point(0, 0), 20, Fill(Color::Red), Stroke(1, Color::Black));
    doc << Circle(
        Point(layout.dimensions.width - 10, layout.dimensions.height - 10), 20,
        Fill(Color::Red), Stroke(1, Color::Black));

    // Create and add all demo shapes
    ShapeColl elements = createSVGElements();
    doc << elements;

    // Save document and report status
    if (doc.save())
    {
        std::cout << "File saved successfully: " << filename << std::endl;
    }
    else
    {
        std::cout << "Failed to save the file: " << filename << std::endl;
    }
}

int main()
{
    try
    {
        // Set canvas dimensions for all layouts
        Dimensions dimensions(500, 500);

        // Define array of all possible coordinate system origins
        const Layout::Origin layouts[] = {Layout::TopLeft, Layout::TopRight,
                                          Layout::BottomLeft,
                                          Layout::BottomRight};

        // Generate SVG file for each coordinate system origin
        for (Layout::Origin origin : layouts)
        {
            Layout layout(dimensions, origin);
            demoDocLayout(layout);
        }
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
