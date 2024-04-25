#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "Layer.h"
#include <vtkImageReader2Factory.h>

class BackgroundImage : public Layer {
private:
  std::string imagePath;
  vtkSmartPointer<vtkImageReader2Factory> readerFactory;

  void updateImage();


public:
  BackgroundImage(std::string imagePath);

  std::string getImagePath();
  void setImagePath(std::string imagePath);
};

#endif
