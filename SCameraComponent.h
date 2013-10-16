#ifndef SCAMERACOMPONENT_H_INCLUDED
#define SCAMERACOMPONENT_H_INCLUDED

#include <lf/Lightfeather.h>
#include <entityx.h>

using namespace lf;
using namespace entityx;

struct CameraComponent : Component<CameraComponent>
{
    f32 fov;
    f32 near;
    f32 far;
    bool clearColorBuffer;
    scene::C3DCamera *cam;
    core::recti viewPort;
    core::CColorI backgroundColor;

    CameraComponent(f32 fov = core::PI / 3.0f, f32 near = 1.0f, f32 far = 1000.0f, bool clearColorBuffer = true) : fov(fov), near(near), far(far), clearColorBuffer(clearColorBuffer)
    {
        cam = new scene::C3DCamera(fov, near, far, clearColorBuffer);
        cam->setBackgroundColor(core::CColorI(0, 0, 0, 0));
    }
    CameraComponent(render::IRenderWindow *rwin, f32 fov = core::PI / 3.0f, f32 near = 1.0f, f32 far = 1000.0f, bool clearColorBuffer = true) : fov(fov), near(near), far(far), clearColorBuffer(clearColorBuffer)
    {
        cam = new scene::C3DCamera(rwin,fov, near, far, clearColorBuffer);
        cam->setBackgroundColor(core::CColorI(0, 0, 0, 0));
    }
    CameraComponent(core::recti viewport, f32 fov = core::PI / 3.0f, f32 near = 1.0f, f32 far = 1000.0f, bool clearColorBuffer = true) : fov(fov), near(near), far(far), clearColorBuffer(clearColorBuffer)
    {
        cam = new scene::C3DCamera(fov, near, far, clearColorBuffer);
        cam->setViewPort(viewport);
        cam->setBackgroundColor(core::CColorI(0, 0, 0, 0));
    }
    // use this for switching between minicams to fullscreen and back (e.g. radar, rearview...)
    void setViewPort(core::recti viewPort)
    {
        viewPort = viewPort;
        cam->setViewPort(viewPort);
    }
    void setViewPort(render::IRenderWindow *rwin)
    {
        cam->setViewPort(core::recti(0,0,rwin->getInnerSize().X, rwin->getInnerSize().Y));
    }

};

#endif // SCAMERACOMPONENT_H_INCLUDED
