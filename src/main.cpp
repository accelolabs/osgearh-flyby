#include <iostream>
#include <osg/ArgumentParser>
#include "option/Option.h"

int main(int argc, char** argv)
{
    osg::ArgumentParser arguments(&argc, argv);
    Options options;

    if (printHelp(arguments)) {
        return 0;
    }

    if (!parseOptions(arguments, options)) {
        return 1;
    }

    std::cout
        << "Parsed:\n"
        << options.altitude << " \n"
        << options.latitude << " \n"
        << options.longitude << " \n"
        << options.yaw << " \n"
        << options.pitch << " \n"
        << options.roll << " \n"
        << options.width << " \n"
        << options.height << " \n"
        << options.outputFile << " \n"
        << options.earthFile << " \n";

    return 0;
}
