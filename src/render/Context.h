#pragma once

#include <osg/GraphicsContext>
#include <osg/ref_ptr>


osg::ref_ptr<osg::GraphicsContext> createContext(int width, int height);
