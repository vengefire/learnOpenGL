#pragma once

#include "../../config.h"

namespace openGL::textures
{
  class TextureBase
  {
  public:
    TextureBase();
    virtual ~TextureBase();

    void loadFromFile(std::string textureFilePath, bool flipVertically = true);

    unsigned int getTextureID() const { return textureID_; }
    int getImageWidth() const { return imageWidth_; }
    int getImageHeight() const { return imageHeight_; }
    int getImageChannels() const { return imageChannels_; }
    void bind(unsigned int textureCnt);

  protected:
    void init();

  private:
    unsigned int textureID_;
    int imageWidth_, imageHeight_, imageChannels_;
  };
}
