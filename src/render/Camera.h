#pragma once

#include <osg/Vec3d>
#include "../option/Option.h"

bool getCameraVectors(
    const Options& options,
    osg::Vec3d& cameraPosWorld,
    osg::Vec3d& viewDirWorld,
    osg::Vec3d& upDirWorld
);
