#ifndef CAMERAMOVECALLBACK_H
#define CAMERAMOVECALLBACK_H


#include <vtkCallbackCommand.h>
#include <vtkCamera.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkMatrix4x4.h>

class CameraMoveCallback : public vtkCallbackCommand {

public:
    /** Create new instance using the vtk New template.
       */
    static CameraMoveCallback *New(vtkCamera *cam);

    /** Constructor.
      */
    CameraMoveCallback();

    /** Sets the camera to operate on.
      */
    void setCam(const vtkSmartPointer<vtkCamera> &cam);

private:
    /** The camera to operate on.
      */ 
    vtkSmartPointer<vtkCamera> cam;

    /** Event controller. Should be subscribed to keyPressEvent and MouseWheelForward/MouseWheelBackward events.
      */ 
    void Execute(vtkObject *caller, unsigned long evId, void *callData) override;

    /** Zooms the camera in or out.
      * @param in : whether to zoom in or out.
      */
    void zoom(const bool in);

    /** Pans the camera in a direction, determined by the parameter.
      * 'h' and 'left' : pan left
      * 'j' and 'up' : pan up
      * 'k' and 'down' : pan down
      * 'l' and 'right' : pan right
      * @param dir : string of the pressed keycode.
      */
    void pan(const std::string dir);

    /** Edits the camera such that it only ever renders within the [-1,1] normalised coordinate field.
      * Does so by making sure that the position of the camera (on the x,y axes), combined with the parallel scale, is never > 1.
      * @param pos : pointer to new desired camera position. This will be changed if it would cause points outside [-1,1] to be displayed.
      */  
    void clampCamera(double *pos);
};


#endif 
