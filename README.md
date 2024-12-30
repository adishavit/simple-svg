# simple-svg

Easy to use SVG library for C++ (fork)

This library is a single file header-only C++ library for creating SVG files.

Simple-SVG was written to provide an easy API to allow beginners to become more accustomed to C++ by easily creating graphics.

This project creates files that can then be viewed by a sister project [File Monitor](http://code.google.com/p/file-monitor). As you make changes to your SVG document, you will automatically see an updated image in File Monitor.

This is a fork/clone of the original code [here](https://code.google.com/p/simple-svg/).

## Build Instructions

```
mkdir build
cd build
cmake ..
make
```

This will create the demo executable `simple_svg` and the test executable `simple_svg_test`, and run the tests.

You can run the demo with:

```
simple_svg
```

to create a demo SVG file, `my_svg.svg`.

You can run the tests with:

```
ctest
```

or with

```
simple_svg_test
```

to see the details of the tests.
