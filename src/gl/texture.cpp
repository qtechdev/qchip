#include <cstddef>

#include <glad/glad.h>

#include "texture.hpp"

Texture create_texture_from_data(
  const std::size_t width, const std::size_t height, const std::size_t channels,
  const unsigned char *data
) {
  GLuint texture;
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  GLenum fmt;
  switch (channels) {
    case 1: fmt = GL_RED; break;
    case 2: fmt = GL_RG; break;
    case 4: fmt = GL_RGBA; break;
    default: fmt = GL_RGB;
  }

  glTexImage2D(
    GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, fmt, GL_UNSIGNED_BYTE, data
  );

  glBindTexture(GL_TEXTURE_2D, 0);

  return {texture};
}

void bindTexture(const Texture &t) {
  if (current_texture != t.id) {
    glBindTexture(GL_TEXTURE_2D, t.id);
    current_texture = t.id;
  }
}
