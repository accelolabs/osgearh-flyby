#include "Capture.h"

#include <chrono>

#include <osg/Camera>
#include <osg/GraphicsContext>
#include <osg/Image>
#include <osg/Viewport>
#include <osgViewer/Viewer>

#include "Context.h"


void prepareHeadlessScene(osgViewer::Viewer& viewer, int renderSeconds) {
    const auto start = std::chrono::steady_clock::now();
    while (true) {
        viewer.frame();

        const auto now = std::chrono::steady_clock::now();
        const std::chrono::duration<double> elapsed = now - start;
        if (elapsed.count() >= renderSeconds) {
            break;
        }
    }
}

osg::ref_ptr<osg::Image> capture(
    osg::Node* scene,
    const Options& options,
    const osg::Vec3d& cameraPosWorld,
    const osg::Vec3d& viewDirWorld,
    const osg::Vec3d& upDirWorld
) {
    osg::ref_ptr<osg::GraphicsContext> graphicsContext = createContext(options.width, options.height);
    if (!graphicsContext || !graphicsContext->valid()) {
        return nullptr;
    }

    osgViewer::Viewer viewer;
    viewer.setThreadingModel(osgViewer::Viewer::SingleThreaded);
    viewer.setSceneData(scene);

    osg::Camera* camera = viewer.getCamera();
    camera -> setGraphicsContext(graphicsContext);
    camera -> setViewport(new osg::Viewport(0, 0, options.width, options.height));

    camera -> setDrawBuffer(GL_BACK);
    camera -> setReadBuffer(GL_BACK);
    camera -> setClearMask(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    camera -> setClearColor(osg::Vec4f(0.0f, 0.0f, 0.0f, 1.0f));

    double aspectRatio = static_cast<double>(options.width) / static_cast<double>(options.height);
    camera -> setProjectionMatrixAsPerspective(options.fov, aspectRatio, 1.0, 1.0e8);
    camera -> setViewMatrixAsLookAt(cameraPosWorld, cameraPosWorld + viewDirWorld, upDirWorld);
    
    osg::StateSet* stateSet = camera -> getOrCreateStateSet();
    stateSet -> setMode(GL_LIGHTING, osg::StateAttribute::OFF);
    stateSet -> setMode(GL_NORMALIZE, osg::StateAttribute::OFF);

    osg::ref_ptr<osg::Image> image = new osg::Image();
    camera -> attach(osg::Camera::COLOR_BUFFER, image.get());

    viewer.realize();

    prepareHeadlessScene(viewer, options.renderSeconds);

    viewer.stopThreading();

    if (auto* databasePager = viewer.getDatabasePager()) {
        databasePager -> cancel();
    }

    if (auto* ImagePager = viewer.getImagePager()) {
        ImagePager -> cancel();
    }

    viewer.setDone(true);

    return image;
}
