#pragma once

#include <string>
#include <osg/ArgumentParser>

struct Options {
    std::string earthFile = "";
    std::string outputFile = "";
    std::string sharedName = "";

    double altitude = 0.0;
    double latitude = 0.0;
    double longitude = 0.0;

    double yaw = 0.0;
    double pitch = 0.0;
    double roll = 0.0;

    int width = 512;
    int height = 512;

    double fov = 45;
    int renderSeconds = 10;
};

bool printHelp(osg::ArgumentParser &arguments);

bool parseOptions(osg::ArgumentParser& arguments, Options& options);
