#ifndef VTKBASE_CAMERAMOVECALLBACK_H
#define VTKBASE_CAMERAMOVECALLBACK_H


#include <vtkCallbackCommand.h>
#include <vtkCamera.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkMatrix4x4.h>

class CameraMoveCallback : public vtkCallbackCommand {

public:
    static CameraMoveCallback *New(vtkCamera *cam);
    CameraMoveCallback();

    void setCam(const vtkSmartPointer<vtkCamera> &cam);

private:
    vtkSmartPointer<vtkCamera> cam;

    void Execute(vtkObject *caller, unsigned long evId, void *callData) override;
    void zoom(const bool in);
    void pan(const std::string dir);
};


#endif 
