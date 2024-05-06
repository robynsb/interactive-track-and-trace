#include <vtkCamera.h>
#include <vtkTransformFilter.h>
#include "advection/UVGrid.h"

#ifndef VTKBASE_NORMALISEDCARTOGRAPHICCAMERA_H
#define VTKBASE_NORMALISEDCARTOGRAPHICCAMERA_H

#endif //VTKBASE_NORMALISEDCARTOGRAPHICCAMERA_H

/**
 * Constructs a orthographically projected camera that looks at the square x,y in [-1, 1] with z = 0 and w = 1.
 * The space [-1,1] x [-1,1] x {0} will be referred to as the normalised space.
 * @return pointer to camera
 */
vtkSmartPointer<vtkCamera> createNormalisedCamera();

/**
 * Constructs a 4x4 projection matrix that maps homogenious (longitude, latitude, 0, 1) points
 * to the normalised space.
 * TODO: This transformation has room for improvement see:
 * https://github.com/MakeNEnjoy/interactive-track-and-trace/issues/12
 * @return pointer to 4x4 matrix
 */
vtkSmartPointer<vtkMatrix4x4> getCartographicTransformMatrix(const std::shared_ptr<UVGrid> uvGrid);

/**
 * Convenience function that converts the 4x4 projection matrix into a vtkTransformFilter
 * @return pointer to transform filter
 */
vtkSmartPointer<vtkTransformFilter> createCartographicTransformFilter(const std::shared_ptr<UVGrid> uvGrid);