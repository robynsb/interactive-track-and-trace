#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "Layer.h"
#include <vtkImageReader2Factory.h>

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


  void setCamera(vtkCamera *cam) override;
};

#endif
