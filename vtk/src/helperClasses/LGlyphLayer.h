#ifndef LGLYPHLAYER_H
#define LGLYPHLAYER_H

#include "Layer.h"
#include "SpawnPointCallback.h"
#include <vtkPolyData.h>
#include <vtkInteractorStyle.h>

/** Implements the Layer class for the case of a Lagrangian visualization.
  * Specifically, this class models the Lagrangian particles in the simulation using the 'glyph' mark and 'transparency' channel to denote age.
  */
class LGlyphLayer : public Layer {
private:
  vtkSmartPointer<vtkPoints> points;
  vtkSmartPointer<vtkPolyData> data;



public:
  /** Constructor.
    */
  LGlyphLayer();

  /** This function spoofs a few points in the dataset. Mostly used for testing.
    */
  void spoofPoints();

  /** updates the glyphs to reflect the given timestamp in the dataset.
    * @param t : the time at which to fetch the data.
    */
  void updateData(int t) override;

  vtkSmartPointer<SpawnPointCallback> createSpawnPointCallback();
};

#endif
