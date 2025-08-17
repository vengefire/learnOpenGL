#include "TextureBase.h"
#include "../../dep/stb/stb_image.h"

namespace openGL::textures
{
  TextureBase::TextureBase()
  {
    init();
  }

  TextureBase::~TextureBase()
  {
    glDeleteTextures(1, &textureID_);
    std::cout << "Texture with ID: " << textureID_ << " deleted." << std::endl;
  }

  void TextureBase::init()
  {
    glGenTextures(1, &textureID_);
    glBindTexture(GL_TEXTURE_2D, textureID_);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    std::cout << "Texture initialized with ID: " << textureID_ << std::endl;
  }

  void TextureBase::loadFromFile(std::string textureFilePath, bool flipVertically)
  {
    std::cout << "Loading texture from file: " << textureFilePath << std::endl;
    stbi_set_flip_vertically_on_load(flipVertically);
    unsigned char* data = stbi_load(textureFilePath.c_str(), &imageWidth_, &imageHeight_, &imageChannels_, 0);
    if (!data)
    {
      throw std::runtime_error("Failed to load texture: " + textureFilePath);
    }
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imageWidth_, imageHeight_, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);
    std::cout << "Texture loaded successfully: " << textureFilePath << std::endl;
  }

  void TextureBase::bind(unsigned int textureCnt)
  {
    glActiveTexture(GL_TEXTURE0 + textureCnt);
    glBindTexture(GL_TEXTURE_2D, textureID_);
  }

} // namespace openGL::textures
