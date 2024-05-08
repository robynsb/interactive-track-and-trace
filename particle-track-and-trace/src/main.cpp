#include <netcdf>
#include <vtkActor2D.h>
#include <vtkNamedColors.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper2D.h>
#include <vtkProperty2D.h>
#include <vtkRenderer.h>
#include <vtkVertexGlyphFilter.h>
#include <memory>

#include "layers/BackgroundImage.h"
#include "layers/EGlyphLayer.h"
#include "layers/LGlyphLayer.h"
#include "Program.h"
#include "advection/UVGrid.h"
#include "advection/kernel/RK4AdvectionKernel.h"
#include "advection/kernel/SnapBoundaryConditionKernel.h"

#include <vtkTransform.h>
#include <vtkTransformFilter.h>
#include <vtkGeoProjection.h>
#include <vtkGeoTransform.h>
#include <vtkGeneralTransform.h>

using namespace std;

#define DT 60 * 60 // 60 sec/min * 60 mins

int main() {
  cout << "Reading data..." << endl;
  shared_ptr<UVGrid> uvGrid = make_shared<UVGrid>();
  auto kernelRK4 = make_unique<RK4AdvectionKernel>(uvGrid);
  auto kernelRK4BoundaryChecked = make_unique<SnapBoundaryConditionKernel>(std::move(kernelRK4), uvGrid);
  cout << "Starting vtk..." << endl;

  auto l = new LGlyphLayer(uvGrid, std::move(kernelRK4BoundaryChecked));
  l->spoofPoints();

  unique_ptr<Program> program = make_unique<Program>(DT);
  program->addLayer(new BackgroundImage("../../../../data/map_661-661.png"));
  program->addLayer(new EGlyphLayer(uvGrid));
  program->addLayer(l);

  program->render();

//  auto proj = vtkSmartPointer<vtkGeoProjection>::New(); proj->SetName("merc"); auto geoTransform = vtkSmartPointer<vtkGeoTransform>::New(); geoTransform->SetDestinationProjection(proj);
//  const double XMin = -15.875;
//  const double XMax = 12.875;
//  const double YMin = 46.125;
//  const double YMax = 62.625;
//
//  double bottomLeft[3] = {XMin, YMin, 0};
//  double topRight[3] = {XMax, YMax, 0};
//  geoTransform->TransformPoint(bottomLeft, bottomLeft);
//  geoTransform->TransformPoint(topRight, topRight);
//
//  double width = topRight[0] - bottomLeft[0];
//  double height = topRight[1] - bottomLeft[1];
//
//  auto scaleIntoNormalisedSpace = vtkSmartPointer<vtkTransform>::New();
//  scaleIntoNormalisedSpace->Scale(2/(width), 2/(height), 1);
//  scaleIntoNormalisedSpace->Translate(-(bottomLeft[0]+topRight[0])/2, -(bottomLeft[1] + topRight[1])/2, 0);
//
//  auto totalProjection = vtkSmartPointer<vtkGeneralTransform>::New();
//  totalProjection->PostMultiply();
//  totalProjection->Identity();
//  totalProjection->Concatenate(geoTransform);
//  totalProjection->Concatenate(scaleIntoNormalisedSpace);
//
//  double in[3] = {4.846871030623073, 52.364810061968335, 0};
//  geoTransform->TransformPoint(in, in);
//  cout << "in[3] = {" << in[0] << "," << in[1] << "," << in[2] << "}" << endl;
//  scaleIntoNormalisedSpace->TransformPoint(in, in);
//  cout << "in[3] = {" << in[0] << "," << in[1] << "," << in[2] << "}" << endl;
//  scaleIntoNormalisedSpace->Inverse();
//  scaleIntoNormalisedSpace->TransformPoint(in, in);
//  cout << "in[3] = {" << in[0] << "," << in[1] << "," << in[2] << "}" << endl;
//  geoTransform->Inverse();
//  geoTransform->TransformPoint(in, in);
//  cout << "in[3] = {" << in[0] << "," << in[1] << "," << in[2] << "}" << endl;
////  totalProjection->TransformPoint(in, in);
////  cout << "in[3] = {" << in[0] << "," << in[1] << "," << in[2] << "}" << endl;
////  totalProjection->Inverse();
////  totalProjection->TransformPoint(in, in);
////  cout << "in[3] = {" << in[0] << "," << in[1] << "," << in[2] << "}" << endl;

  return EXIT_SUCCESS;
}

