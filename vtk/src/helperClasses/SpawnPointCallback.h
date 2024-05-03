#ifndef VTKBASE_SPAWNPOINTCALLBACK_H
#define VTKBASE_SPAWNPOINTCALLBACK_H


#include <vtkCallbackCommand.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>

class SpawnPointCallback : public vtkCallbackCommand {

public:
    static SpawnPointCallback *New();
    SpawnPointCallback();

    void setPoints(const vtkSmartPointer<vtkPoints> &points);

    void setData(const vtkSmartPointer<vtkPolyData> &data);

private:
    vtkSmartPointer<vtkPolyData> data;
    vtkSmartPointer<vtkPoints> points;
public:

private:
    void Execute(vtkObject *caller, unsigned long evId, void *callData) override;
    bool dragging = false;
};


#endif //VTKBASE_SPAWNPOINTCALLBACK_H
