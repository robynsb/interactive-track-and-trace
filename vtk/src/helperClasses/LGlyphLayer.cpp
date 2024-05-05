#include "LGlyphLayer.h"
#include "SpawnPointCallback.h"
#include <vtkActor2D.h>
#include <vtkGlyph2D.h>
#include <vtkGlyphSource2D.h>
#include <vtkNamedColors.h>
#include <vtkPolyDataMapper2D.h>
#include <vtkProperty2D.h>
#include <vtkVertexGlyphFilter.h>
#include <vtkInteractorStyle.h>
#include <vtkInteractorStyleUser.h>


vtkSmartPointer<SpawnPointCallback> LGlyphLayer::createSpawnPointCallback() {
    auto newPointCallBack = vtkSmartPointer<SpawnPointCallback>::New();
    newPointCallBack->setData(data);
    newPointCallBack->setPoints(points);
    return newPointCallBack;
}


// TODO: how do we handle mapping between pixelspace and lat/lon (needed for advection)? Current idea: store the vtkPoints in lat/lon system, then apply a transformfilter to map them to the current window geometry. This should allow for a changing viewport as well - we can query the new camera position and map accordingly.
// Further notes; current thinking is to allow tracking a particle's age by using a scalar array in the VtkPolyData. This would be incremented for every tick/updateData function call.
// Another challenge is the concept of beaching; dead particles must not be included in the advect function call (wasted computations), but they should not be outright deleted from the vtkPoints either (we still want to display them). Working Solution: have another array of ints in the vtkPolyData, which tracks for how many calls of UpdateData a given particle has not had its position changed. If this int reaches some treshold (5? 10? 3? needs some testing), exclude the particle from the advect call.
//
// TODO: modelling all this in vtkClasses is workable, but ideally i would want to work with a native C++ class. See if this is doable and feasible.

LGlyphLayer::LGlyphLayer() {
  this->ren = vtkSmartPointer<vtkRenderer>::New();
  this->ren->SetLayer(2);

  this->points = vtkSmartPointer<vtkPoints>::New();
  this->data = vtkSmartPointer<vtkPolyData>::New();
  this->data->SetPoints(this->points);
  
  vtkNew<vtkGlyphSource2D> circleSource;
  circleSource->SetGlyphTypeToCircle();
  circleSource->SetScale(15); 
  circleSource->Update();

  vtkNew<vtkGlyph2D> glyph2D;
  glyph2D->SetSourceConnection(circleSource->GetOutputPort());
  glyph2D->SetInputData(this->data);
  glyph2D->SetColorModeToColorByScalar();
  glyph2D->Update();

  vtkNew<vtkPolyDataMapper2D> mapper;
  mapper->SetInputConnection(glyph2D->GetOutputPort());
  mapper->Update();

  vtkNew<vtkActor2D> actor;
  actor->SetMapper(mapper);
  actor->GetProperty()->SetColor(1,1,1);

  this->ren->AddActor(actor);
}

// creates a few points so we can test the updateData function
void LGlyphLayer::spoofPoints() {
  this->points->InsertNextPoint(53, 2, 0);
  this->points->InsertNextPoint(48.2, 111.01, 0);
  this->points->InsertNextPoint(331, 331, 0);

  this->points->Modified();
}


// returns new coords for a point; used to test the updateData function
std::pair<double, double> advect(int time, double lat, double lon) {
  return {lat+0.1, lon+0.1} ;
}


// converts a x,y pair from pixel coordinates to real world latitude and longitude.
// TODO: make this more modular by having it interact with the backgroundImage layer (and possibly the camera panning/zooming logic when that is implemented).
std::pair<double, double> pixelToReal(double x, double y) {
  //assumes a 661x661 window with a range of [46.125, 62.625] lat and [-15.875, 12.875] lon.
  return {(x*25+46125)/1000, (y*43.5-15875)/1000};
}

// converts a lat,lon pair from real world values to pixel coordinates.
// TODO: see above.
std::pair<double, double> realToPixel(double lat, double lon) {
  //assumes a 661x661 window with a range of [46.125, 62.625] lat and [-15.875, 12.875] lon.
  return {(lat*1000-46125)/25, (lon*1000+15875)/43.5};
}

// FIXME: actually the above functions are a bit of a naive way of modelling these. Much better would be to have the points at the real-world latitude and longitude, and apply a filter in the pipeline to convert them to the appropriate window geometry.
 void LGlyphLayer::updateData(int t) {
  double point[3];
  for (vtkIdType n=0; n < this->points->GetNumberOfPoints(); n++) {
    this->points->GetPoint(n, point);
    auto grads = pixelToReal(point[0], point[1]);
    auto newGrads = advect(n, grads.first, grads.second);
    auto newPixs = realToPixel(newGrads.first, newGrads.second);
    this->points->SetPoint(n, newPixs.first, newPixs.second, 0);
  }
  this->points->Modified();
}
