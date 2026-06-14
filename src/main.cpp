#include <osgEarth/MapNode>
#include <osgEarth/TMS>
#include <osgEarth/EarthManipulator>
#include <osgEarth/GLUtils>
#include <osg/ArgumentParser>
#include <osgViewer/Viewer>

int main(int argc, char** argv)
{
    osgEarth::initialize();
    
    osg::ArgumentParser args(&argc, argv);
    osgViewer::Viewer viewer(args);
    viewer.setRealizeOperation(new osgEarth::GL3RealizeOperation());
    
    auto imagery = new osgEarth::TMSImageLayer();
    imagery->setURL("https://readymap.org/readymap/tiles/1.0.0/7/");
    
    auto mapNode = new osgEarth::MapNode();
    mapNode->getMap()->addLayer(imagery);
    
    viewer.setSceneData(mapNode);
    viewer.setCameraManipulator(new osgEarth::EarthManipulator(args));
    
    return viewer.run();
}
