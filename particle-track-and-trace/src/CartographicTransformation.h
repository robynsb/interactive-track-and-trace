#ifndef NORMALISEDCARTOGRAPHICCAMERA_H
#define NORMALISEDCARTOGRAPHICCAMERA_H

#include <memory>
#include <vtkCamera.h>
#include <vtkTransformFilter.h>
#include "advection/UVGrid.h"


/**
 * Constructs a orthographically projected camera that looks at the square x,y in [-1, 1] with z = 0 and w = 1.
 * The space [-1,1] x [-1,1] x {0} will be referred to as the normalised space.
 * @return pointer to camera
 */
vtkSmartPointer<vtkCamera> createNormalisedCamera();

/**
 *  Creates a mercator projection and then scales into normalised space.
 *  @param uvGrid grid that contains latitudes and longitudes
 *  @return pointer to transform filter
 */
vtkSmartPointer<vtkTransformFilter> createCartographicTransformFilter(const std::shared_ptr<UVGrid> uvGrid);

/**
 * Creates an inverse mercator projection and then scales into normalised space.
 *
 * Note that it is not possible to call the Inverse() member function on the transform of the
 * createCartographicTransformFilter. It produces the wrong output,
 * I believe that this is a bug in VTK, I might make an issue about this sometime.
 * @param uvGrid grid that contains latitudes and longitudes
 * @return pointer to transform filter
 */
vtkSmartPointer<vtkTransformFilter> createInverseCartographicTransformFilter(const std::shared_ptr<UVGrid> uvGrid);
#endif //NORMALISEDCARTOGRAPHICCAMERA_H
