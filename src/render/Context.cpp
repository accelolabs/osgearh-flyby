#include "Context.h"

osg::ref_ptr<osg::GraphicsContext> createContext(int width, int height) {
    osg::ref_ptr<osg::GraphicsContext::Traits> traits = new osg::GraphicsContext::Traits();

    traits -> x = 0;
    traits -> y = 0;
    traits -> width = width;
    traits -> height = height;

    traits -> doubleBuffer = true;
    traits -> pbuffer = true;
    traits -> sharedContext = nullptr;

    osg::ref_ptr<osg::GraphicsContext> graphicsContext = osg::GraphicsContext::createGraphicsContext(traits.get());

    if (!graphicsContext || !graphicsContext -> valid()) {
        traits -> pbuffer = false;
        graphicsContext = osg::GraphicsContext::createGraphicsContext(traits.get());
    }

    return graphicsContext;
}
