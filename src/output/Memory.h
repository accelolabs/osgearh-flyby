#pragma once

#include <string>

#include <osg/Image>
#include <osg/ref_ptr>

bool linuxSaveToShm(const osg::ref_ptr<osg::Image> image, const std::string& sharedName);
