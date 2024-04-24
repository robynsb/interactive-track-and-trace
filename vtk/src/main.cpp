#include <vtkActor.h>
#include <vtkActor2D.h>
#include <vtkCamera.h>
#include <vtkDoubleArray.h>
#include <vtkMapper2D.h>
#include <vtkImageReader2.h>
#include <vtkImageData.h>
#include <vtkImageActor.h>
#include <vtkImageReader2Factory.h>
#include <vtkNamedColors.h>
#include <vtkNew.h>
#include <vtkPolyDataMapper.h>
#include <vtkPolyDataMapper2D.h>
#include <vtkProgrammableGlyphFilter.h>
#include <vtkSmartPointer.h>
#include <vtkProperty.h>
#include <vtkProperty2D.h>
#include <vtkRectilinearGrid.h>
#include <vtkRectilinearGridGeometryFilter.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>

#include <netcdf>
#include <vtkVertexGlyphFilter.h>

#define NLATS 67
#define NLONS 116

using namespace std;
using namespace netCDF;

template <typename T>
vector<T> getVarVector(const NcVar &var) {
    int length = 1;
    for (NcDim dim : var.getDims()) {
        length *= dim.getSize();
    }

    vector<T> vec(length);

    var.getVar(vec.data());

    return vec;
}

tuple<vector<int>, vector<double>, vector<double>> readGrid() {
    netCDF::NcFile data("../../../../data/grid.h5", netCDF::NcFile::read);
    multimap< string, NcVar > vars = data.getVars();
    vector<int> time = getVarVector<int>(vars.find("times")->second);
    vector<double> longitude = getVarVector<double>(vars.find("longitude")->second);
    vector<double> latitude = getVarVector<double>(vars.find("latitude")->second);

    return {time, latitude, longitude};
}


void renderCoordinates(vtkRenderer *ren, vtkNamedColors *colors) {

  vtkNew<vtkPoints> points;
  auto [times, lats, lons] = readGrid();

  double i = 0;
  for (double lat : lats) {
    for (double lon : lons) {
      cout << "lat: " << (lat*1000-46125)*661/16500 << "\t lon: " << (lon*1000+15875)*661/28750 << endl;
      points->InsertNextPoint((lat*1000-46125)*661/16500, (lon*1000+15875)*661/28750, 0);
    }
  }

  vtkNew<vtkPolyData> polydata;
  polydata->SetPoints(points);

  vtkNew<vtkVertexGlyphFilter> glyphFilter;
  glyphFilter->SetInputData(polydata);
  glyphFilter->Update();

  vtkNew<vtkPolyDataMapper2D> mapper;
  mapper->SetInputConnection(glyphFilter->GetOutputPort());
  mapper->Update();

  vtkNew<vtkActor2D> actor;
  actor->SetMapper(mapper);
  actor->GetProperty()->SetColor(colors->GetColor3d("Gold").GetData());
  actor->GetProperty()->SetPointSize(3);

  ren->AddActor(actor);
}

void renderBackground(vtkRenderer *background) {
  vtkSmartPointer<vtkImageData> imageData;

  vtkNew<vtkImageReader2Factory> readerFactory;
  vtkSmartPointer<vtkImageReader2> imageReader;
  
  imageReader.TakeReference(readerFactory->CreateImageReader2("../../../../data/map_661-661.png"));
  imageReader->SetFileName("../../../../data/map_661-661.png");
  imageReader->Update();
  imageData = imageReader->GetOutput();

  vtkNew<vtkImageActor> imageActor;
  imageActor->SetInputData(imageData);

  background->AddActor(imageActor);


  // camera stuff
  // essentially sets the camera to the middle of the background, and points it at the background
  double origin[3], spacing[3];
  int extent[6];
  imageData->GetOrigin(origin);
  imageData->GetSpacing(spacing);
  imageData->GetExtent(extent);

  vtkCamera *camera = background->GetActiveCamera();
  camera->ParallelProjectionOn();

  double xc = origin[0] + 0.5 * (extent[0] + extent[1]) * spacing[0];
  double yc = origin[1] + 0.5 * (extent[2] + extent[3]) * spacing[1];
  double yd = (extent[3] - extent[2] + 1) * spacing[1];
  double d = camera->GetDistance();
  camera->SetParallelScale(0.5 * yd);
  camera->SetFocalPoint(xc, yc, 0.0);
  camera->SetPosition(xc, yc, d);
}

int main() {
  vtkNew<vtkNamedColors> colors;
  vtkNew<vtkRenderer> Euler, Background, Lagrange;
  Euler->SetBackground(colors->GetColor3d("DarkSlateGray").GetData());


  Background->SetLayer(0);
  Background->InteractiveOff();
  Euler->SetLayer(1);
  Euler->InteractiveOff();
  Lagrange->SetLayer(2);

  renderCoordinates(Euler, colors);
  renderBackground(Background);

  vtkNew<vtkRenderWindow> renWin;
  renWin->SetNumberOfLayers(3);
  // renWin->SetNumberOfLayers(2);
  renWin->AddRenderer(Background);
  renWin->AddRenderer(Euler);
  renWin->AddRenderer(Lagrange);
  renWin->SetWindowName("Simulation");
  renWin->SetSize(661, 661);

  vtkNew<vtkRenderWindowInteractor> iren;
  iren->SetRenderWindow(renWin);

  renWin->Render();
  iren->Start();


  return EXIT_SUCCESS;
}

