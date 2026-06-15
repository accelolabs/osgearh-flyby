#include "Camera.h"

#include <osg/Matrixd>
#include <osg/Vec3d>
#include <osgEarth/GeoData>
#include <osgEarth/SpatialReference>

void rotateBasis(osg::Vec3d& v1, osg::Vec3d& v2, const osg::Vec3d& axis, double degrees) {
    osg::Quat rotation(osg::DegreesToRadians(degrees), axis);
    v1 = rotation * v1;
    v2 = rotation * v2;
}

bool getCameraVectors(
    const Options& options,
    osg::Vec3d& cameraPosWorld,
    osg::Vec3d& viewDirWorld,
    osg::Vec3d& upDirWorld
) {
    const osgEarth::SpatialReference* wgs84 = osgEarth::SpatialReference::get("wgs84");
    osgEarth::GeoPoint planePoint(
        wgs84,
        options.longitude,
        options.latitude,
        options.altitude,
        osgEarth::ALTMODE_ABSOLUTE
    );

    // transform matrix ENU -> ECEF
    osg::Matrixd toWorld;
    if (!planePoint.toWorld(cameraPosWorld) || !planePoint.createLocalToWorld(toWorld)) {
        return false;
    }

    osg::Vec3d eastLocal(1.0, 0.0, 0.0);
    osg::Vec3d northLocal(0.0, 1.0, 0.0);
    osg::Vec3d upLocal(0.0, 0.0, 1.0);

    rotateBasis(northLocal, eastLocal, upLocal, -options.yaw);
    rotateBasis(northLocal, upLocal, eastLocal, options.pitch);
    rotateBasis(eastLocal, upLocal, northLocal, options.roll);

    viewDirWorld = osg::Matrixd::transform3x3(northLocal, toWorld);
    upDirWorld = osg::Matrixd::transform3x3(upLocal, toWorld);

    viewDirWorld.normalize();
    upDirWorld.normalize();

    return true;
}
