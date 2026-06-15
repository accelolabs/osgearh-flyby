#include <iostream>
#include "Option.h"

bool printHelp(osg::ArgumentParser &arguments) {
    if (arguments.read("-h") || arguments.read("--help")) {
        std::cout
            << "Usage: osgearth-flyby [options]\n"
            << "Required arguments:\n"
            << "    --earth <file>       osgEarth file\n"
            << "    --altitude <m>       UAV altitude\n"
            << "    --latitude <deg>     UAV latitude\n"
            << "    --longitude <deg>    UAV longitude\n"
            << "    --yaw <deg>          UAV yaw\n"
            << "    --pitch <deg>        UAV pitch\n"
            << "    --roll <deg>         UAV roll\n"
            << "Optional arguments:\n"
            << "    --width <int>        Output image width (512)\n"
            << "    --height <int>       Output image height (512)\n"
            << "    --fov <deg>          Virtual camera FOV (45)\n"
            << "    --output <file>      Output file (flyby.png)\n";
        return true;
    }

    return false;
}

bool parseOptions(osg::ArgumentParser &arguments, Options &options) {
    if (!arguments.read("--earth", options.earthFile)) {
        std::cerr << "Error: --earth <file> is required.\n";
        return false;
    }

    if (!arguments.read("--altitude", options.altitude)) {
        std::cerr << "Error: --altitude is required.\n";
        return false;
    }
    if (!arguments.read("--latitude", options.latitude)) {
        std::cerr << "Error: --latitude is required.\n";
        return false;
    }
    if (!arguments.read("--longitude", options.longitude)) {
        std::cerr << "Error: --longitude is required.\n";
        return false;
    }

    if (!arguments.read("--yaw", options.yaw)) {
        std::cerr << "Error: --yaw is required.\n";
        return false;
    }
    if (!arguments.read("--pitch", options.pitch)) {
        std::cerr << "Error: --pitch is required.\n";
        return false;
    }
    if (!arguments.read("--roll", options.roll)) {
        std::cerr << "Error: --roll is required.\n";
        return false;
    }

    arguments.read("--width", options.width);
    arguments.read("--height", options.height);

    arguments.read("--fov", options.fov);

    arguments.read("--output", options.outputFile);

    return true;
}
