#include <iostream>
#include <osg/ArgumentParser>
#include <osg/Node>
#include <osgEarth/Common>
#include <osgDB/ReadFile>
#include <osgDB/WriteFile>
#include <osgEarth/MapNode>
#include "option/Option.h"
#include "render/Camera.h"
#include "render/Capture.h"


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

    osgEarth::initialize(arguments);

    osg::ref_ptr<osg::Node> scene = osgDB::readRefNodeFile(options.earthFile);
    if (!scene.valid()) {
        std::cerr << "Failed to load earth file: " << options.earthFile << "\n";
        return 1;
    }

    osgEarth::MapNode* mapNode = osgEarth::MapNode::get(scene.get());
    if (mapNode == nullptr) {
        std::cerr << "Loaded scene does not contain an osgEarth MapNode\n";
        return 1;
    }

    if (!mapNode->open()) {
        std::cerr << "Failed to open MapNode from earth file\n";
    }

    osg::Vec3d cameraPosWorld;
    osg::Vec3d viewDirWorld;
    osg::Vec3d upDirWorld;
    if (!getCameraVectors(options, cameraPosWorld, viewDirWorld, upDirWorld)) {
        std::cerr << "Failed to construct the UAV camera pose\n";
        return 1;
    }

    osg::ref_ptr<osg::Image> image = capture(scene.get(), options, cameraPosWorld, viewDirWorld, upDirWorld);
    if (!image.valid()) {
        std::cerr << "Failed to capture image\n";
        return 1;
    }

    osgDB::writeImageFile(*image, options.outputFile);
    
    std::cout << "Wrote image to " << options.outputFile << "\n";
    return 0;
}
