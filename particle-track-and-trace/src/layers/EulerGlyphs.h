#ifndef EULERGLYPHS_H
#define EULERGLYPHS_H

#include "Layer.h"
#include <memory>
#include <vtkPolyData.h>

#include "../advection/UVGrid.h"

/**
 * Implements the Layer class for the case of a Eulerian visualization.
 * Specifically, this class models the eulerian flow-fields of the simulation using the 'glyph' mark and 'direction' and 'form' channels to denote direction and strength of velocities.
 */
class EulerGlyphs : public Layer {
public:
  /**
   * Constructor.
    */
  EulerGlyphs(std::shared_ptr<UVGrid> uvGrid);

  /**
   * Updates the glyphs to reflect the given timestamp in the dataset.
   * @param t : the time at which to fetch the data.
   */
  void updateData(int t);
private:
  vtkSmartPointer<vtkPolyData> data;
  vtkSmartPointer<vtkDoubleArray> direction;
  std::shared_ptr<UVGrid> uvGrid;
  int numLats;
  int numLons;

  /** This private function sets up the initial coordinates for the glyphs in the dataset.
    * It also reads some initial data to actually display.
    */
  void readCoordinates();
};


#endif
