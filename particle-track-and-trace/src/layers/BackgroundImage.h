#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "Layer.h"
#include <vtkImageReader2Factory.h>
#include <vtkSmartPointer.h>

/** Implements the Layer class for the case of a background image.
  * Specifically, reads a backgroundImage given by the imagePath attribute and puts it on layer 0.
  */
class BackgroundImage : public Layer {
private:
  std::string imagePath;
  vtkSmartPointer<vtkImageReader2Factory> readerFactory;

  /** This private function updates the background image using the imagePath attribute.
   */
  void updateImage();

  /** This function returns a 4x4matrix which maps the given square of [x0,w] x [y0,h] to the range [-1,1].
    * @param x0 : x coordinate of leftmost edge of image
    * @param y0 : y coordinate of bottommost edge of image
    * @param xMax : x coordinate of rightmost edge of image
    * @param yMax : y coordinate of topmost edge of image
    * @return a 4x4 matrix which transforms the image from its original geometry to the range [-1,1]
    */
  vtkSmartPointer<vtkMatrix4x4> getMatrix(const double x0, const double y0, const int xMax, const int yMax);
  

public:
  /** Constructor.
    * @param imagePath : String to the path of the image to use as background.
    */
  BackgroundImage(std::string imagePath);

  /** Getter.
    * @return the imagePath attribute.
    */
  std::string getImagePath();

  /** Setter. Can be used to change the background image 
    * @param imagePath : String to the path of the new image to use.
    */
  void setImagePath(std::string imagePath);
};

#endif
