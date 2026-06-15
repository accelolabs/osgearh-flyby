#pragma once

#include <osg/Image>
#include <osg/ref_ptr>
#include "../option/Option.h"


osg::ref_ptr<osg::Image> capture(
    osg::Node* scene,
    const Options& options,
    const osg::Vec3d& cameraPosWorld,
    const osg::Vec3d& viewDirWorld,
    const osg::Vec3d& upDirWorld
);
