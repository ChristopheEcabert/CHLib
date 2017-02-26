/**
 *  @file   technique.cpp
 *  @brief  Basic OpenGL program used to render
 *
 *  @author Christophe Ecabert
 *  @date   26/08/16
 *  Copyright © 2016 Christophe Ecabert. All rights reserved.
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <assert.h>

#include "chlib/core/error.hpp"
#include "chlib/core/string_util.hpp"
#include "chlib/ogl/technique.hpp"

/**
 *  @namespace  CHLib
 *  @brief      Chris dev space
 */
namespace CHLib {
  
#pragma mark -
#pragma mark Initialization
  
/*
 *  @name OGLTechnique
 *  @fn OGLTechnique(void)
 *  @brief  Consructor
 */
OGLTechnique::OGLTechnique(void) : shaders_(0), program_(0) {
}

/*
 *  @name ~OGLTechnique
 *  @fn virtual ~OGLTechnique(void)
 *  @brief  Destructor
 */
OGLTechnique::~OGLTechnique(void) {
  // Delete the intermediate shader objects that have been added to the
  // program. The list will only contain something if shaders were compiled
  // but the object itself was destroyed prior to linking.
  for (auto& shader : shaders_) {
    glDeleteShader(shader);
  }
  // Release program
  if (!program_) {
    glDeleteProgram(program_);
    program_ = 0;
  }
}

/*
 *  @name Init
 *  @fn virtual int Init(const std::vector<std::string>& paths)
 *  @brief  Initialized OpenGL program
 *  @param[in]  path  List of shader's files to initialize
 *  @return -1 if error, 0 otherwise
 */
int OGLTechnique::Init(const std::vector<std::string>& paths) {
  program_ = glCreateProgram();
  if (!program_) {
    std::cout << "Error while creating shader program" << std::endl;
    return -1;
  }
  int err = 0;
  for (auto& path : paths) {
    err |= this->AddShader(path);
  }
  return err;
}
  
#pragma mark -
#pragma mark Usage
  
/*
 *  @nme  AddShader
 *  @fn int AddShader(const std::string& filename)
 *  @brief  Add a shader to this technique
 *  @param[in]  filename  Path to the file holding shader
 *  @return -1 if error, 0 otherwise
 */
int OGLTechnique::AddShader(const std::string& filename) {
  int err = -1;
  // Open file
  std::ifstream in(filename.c_str(), std::ios_base::in|std::ios_base::binary);
  if (in.is_open()) {
    // Read content
    std::stringstream sstream;
    sstream << in.rdbuf();
    // Get type of shader
    ShaderType type = this->ExtractShaderType(filename);
    if (type != ShaderType::kUnknownShader) {
      err = this->AddShader(sstream.str(), type);
    } else {
      std::cout << "Unknown shader type" << std::endl;
    }
  } else {
    std::cout << "Unable to open file : " << filename << std::endl;
  }
  return err;
}

/*
 *  @nme  AddShader
 *  @fn int AddShader(const std::string& code, const ShaderType& type)
 *  @brief  Add a shader to this technique
 *  @param[in]  code  Code of the shader to add
 *  @param[in]  type  Type of shader it is
 *  @return -1 if error, 0 otherwise
 */
int OGLTechnique::AddShader(const std::string& code, const ShaderType& type) {
  int err = -1;
  GLuint shader = glCreateShader((GLenum)type);
  if (shader) {
    // Add to shader list
    shaders_.push_back(shader);
    // Set shader source + compile
    const GLchar* data[] = {code.c_str()};
    GLint length[] = {(GLint)code.length()};
    glShaderSource(shader, 1, data, length);
    glCompileShader(shader);
    // Check for error
    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if (status != GL_TRUE) {
      // Compilation fail, get error message
      std::string msg("Compile failure in shader:\n");
      GLint infoLogLength;
      glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);
      char* strInfoLog = new char[infoLogLength + 1];
      glGetShaderInfoLog(shader, infoLogLength, NULL, strInfoLog);
      msg += strInfoLog;
      delete[] strInfoLog;
      // Throw error
      throw CHLib::CHError(CHError::kGeneric, msg, FUNC_NAME);
    } else {
      glAttachShader(program_, shader);
      err = 0;
    }
  } else {
    std::cout << "Unable to create shader" << std::endl;
  }
  return err;
}
  
/*
 *  @name Finalize
 *  @fn int Finalize(void)
 *  @brief  Link OpenGL program
 *  @return -1 if error, 0 othereise
 */
int OGLTechnique::Finalize(void) {
  int err = -1;
  GLint status;
  // Link OpenGL program
  glLinkProgram(program_);
  glGetProgramiv(program_, GL_LINK_STATUS, &status);
  if (!status) {
    std::string msg("Program linking failure :\n");
    GLint infoLogLength;
    glGetProgramiv(program_, GL_INFO_LOG_LENGTH, &infoLogLength);
    char* strInfoLog = new char[infoLogLength + 1];
    glGetProgramInfoLog(program_, infoLogLength, NULL, strInfoLog);
    msg += strInfoLog;
    delete[] strInfoLog;
    // Show error
    throw CHLib::CHError(CHError::kGeneric, msg, FUNC_NAME);
  } else {
    // Everything went smooth, release shader object
    for (auto& shader : shaders_) {
      glDeleteShader(shader);
    }
    shaders_.clear();
    err = glGetError() == GL_NO_ERROR ? 0 : -1;
  }
  return err;
}

/*
 *  @name
 *  @fn
 *  @brief  Activate technique
 */
void OGLTechnique::Use(void) const {
  if (program_) {
    glUseProgram(program_);
  }
}

/*
 *  @name
 *  @fn
 *  @brief  Deactivate technique
 */
void OGLTechnique::StopUsing(void) const {
  glUseProgram(0);
}
  
#pragma mark -
#pragma mark Accessors

/*
 *  @name IsUsing
 *  @fn bool IsUsing(void)
 *  @brief  Indicate if the current program is being used
 *  @return True if currently used
 */
bool OGLTechnique::IsUsing(void) const {
  GLint curr_prog;
  glGetIntegerv(GL_CURRENT_PROGRAM, &curr_prog);
  return (curr_prog == static_cast<GLint>(program_));
}
  
/*
 *  @name Attrib
 *  @fn GLint Attrib(const GLchar* attrib_name)
 *  @brief  Provide the attribute index for a given name
 *  @param[in]  attrib_name Name of the attribute to look for
 *  @return The uniform index for the given name, as returned
 *          from glGetUniformLocation.
 */
GLint OGLTechnique::Attrib(const GLchar* attrib_name) const {
  GLint attrib = -1;
  if (attrib_name != nullptr) {
    attrib = glGetAttribLocation(program_, attrib_name);
  }
  return attrib;
}
  
/*
 *  @name Uniform
 *  @fn GLint Uniform(const GLchar* uniform_name)
 *  @brief  Provide uniform reference for a given name
 *  @param[in]  uniform_name  Name of the uniform to look for
 *  @return The uniform index for the given name, as returned
 *          from glGetUniformLocation.
 */
GLint OGLTechnique::Uniform(const GLchar* uniform_name) const {
  GLint uniform = -1;
  if (uniform_name != nullptr) {
    uniform = glGetUniformLocation(program_, uniform_name);
  }
  return uniform;
}
  
#define ATTRIB_N_UNIFORM_SETTERS(OGL_TYPE, TYPE_PREFIX, TYPE_SUFFIX) \
\
void OGLTechnique::SetAttrib(const GLchar* name, OGL_TYPE v0) \
{ assert(IsUsing()); glVertexAttrib ## TYPE_PREFIX ## 1 ## TYPE_SUFFIX (Attrib(name), v0); } \
void OGLTechnique::SetAttrib(const GLchar* name, OGL_TYPE v0, OGL_TYPE v1) \
{ assert(IsUsing()); glVertexAttrib ## TYPE_PREFIX ## 2 ## TYPE_SUFFIX (Attrib(name), v0, v1); } \
void OGLTechnique::SetAttrib(const GLchar* name, OGL_TYPE v0, OGL_TYPE v1, OGL_TYPE v2) \
{ assert(IsUsing()); glVertexAttrib ## TYPE_PREFIX ## 3 ## TYPE_SUFFIX (Attrib(name), v0, v1, v2); } \
void OGLTechnique::SetAttrib(const GLchar* name, OGL_TYPE v0, OGL_TYPE v1, OGL_TYPE v2, OGL_TYPE v3) \
{ assert(IsUsing()); glVertexAttrib ## TYPE_PREFIX ## 4 ## TYPE_SUFFIX (Attrib(name), v0, v1, v2, v3); } \
\
void OGLTechnique::SetAttrib1v(const GLchar* name, const OGL_TYPE* v) \
{ assert(IsUsing()); glVertexAttrib ## TYPE_PREFIX ## 1 ## TYPE_SUFFIX ## v (Attrib(name), v); } \
void OGLTechnique::SetAttrib2v(const GLchar* name, const OGL_TYPE* v) \
{ assert(IsUsing()); glVertexAttrib ## TYPE_PREFIX ## 2 ## TYPE_SUFFIX ## v (Attrib(name), v); } \
void OGLTechnique::SetAttrib3v(const GLchar* name, const OGL_TYPE* v) \
{ assert(IsUsing()); glVertexAttrib ## TYPE_PREFIX ## 3 ## TYPE_SUFFIX ## v (Attrib(name), v); } \
void OGLTechnique::SetAttrib4v(const GLchar* name, const OGL_TYPE* v) \
{ assert(IsUsing()); glVertexAttrib ## TYPE_PREFIX ## 4 ## TYPE_SUFFIX ## v (Attrib(name), v); } \
\
void OGLTechnique::SetUniform(const GLchar* name, OGL_TYPE v0) \
{ assert(IsUsing()); glUniform1 ## TYPE_SUFFIX (Uniform(name), v0); } \
void OGLTechnique::SetUniform(const GLchar* name, OGL_TYPE v0, OGL_TYPE v1) \
{ assert(IsUsing()); glUniform2 ## TYPE_SUFFIX (Uniform(name), v0, v1); } \
void OGLTechnique::SetUniform(const GLchar* name, OGL_TYPE v0, OGL_TYPE v1, OGL_TYPE v2) \
{ assert(IsUsing()); glUniform3 ## TYPE_SUFFIX (Uniform(name), v0, v1, v2); } \
void OGLTechnique::SetUniform(const GLchar* name, OGL_TYPE v0, OGL_TYPE v1, OGL_TYPE v2, OGL_TYPE v3) \
{ assert(IsUsing()); glUniform4 ## TYPE_SUFFIX (Uniform(name), v0, v1, v2, v3); } \
\
void OGLTechnique::SetUniform1v(const GLchar* name, const OGL_TYPE* v, GLsizei count) \
{ assert(IsUsing()); glUniform1 ## TYPE_SUFFIX ## v (Uniform(name), count, v); } \
void OGLTechnique::SetUniform2v(const GLchar* name, const OGL_TYPE* v, GLsizei count) \
{ assert(IsUsing()); glUniform2 ## TYPE_SUFFIX ## v (Uniform(name), count, v); } \
void OGLTechnique::SetUniform3v(const GLchar* name, const OGL_TYPE* v, GLsizei count) \
{ assert(IsUsing()); glUniform3 ## TYPE_SUFFIX ## v (Uniform(name), count, v); } \
void OGLTechnique::SetUniform4v(const GLchar* name, const OGL_TYPE* v, GLsizei count) \
{ assert(IsUsing()); glUniform4 ## TYPE_SUFFIX ## v (Uniform(name), count, v); }
  
/** Float attribute and uniform setters implementation */
ATTRIB_N_UNIFORM_SETTERS(GLfloat, , f);
  
/*
 * @name  SetUniformMat3
 * @brief Setup uniform value of type Mat3 (generic)
 * @param[in] uniform_name  Uniform name variable to set
 * @param[in] v             Pointer to data
 * @param[in] count         count (default=1)
 * @param[in] transpose     transpose flag (default=false)
 */
void OGLTechnique::SetUniformMat3(const GLchar* name,
                                  const GLfloat* v,
                                  GLsizei count,
                                  GLboolean transpose) {
  assert(IsUsing());
  glUniformMatrix3fv(Uniform(name), count, transpose, v);
}
  
/*
 * @name  SetUniformMat4
 * @brief Setup uniform value of type Mat4 (generic)
 * @param[in] uniform_name  Uniform name variable to set
 * @param[in] v             Pointer to data
 * @param[in] count         count (default=1)
 * @param[in] transpose     transpose flag (default=false)
 */
void OGLTechnique::SetUniformMat4(const GLchar* name,
                                  const GLfloat* v,
                                  GLsizei count,
                                  GLboolean transpose) {
  assert(IsUsing());
  glUniformMatrix4fv(Uniform(name), count, transpose, v);
}
  
/*
 * @name  SetUniform
 * @brief Setup uniform value of type Mat3
 * @param[in] uniform_name  Uniform name variable to set
 * @param[in] m             Matrix data
 * @param[in] transpose     transpose flag (default=false)
 */
void OGLTechnique::SetUniform(const GLchar* uniform_name,
                              const Matrix3<float>& m,
                              GLboolean transpose) {
  assert(IsUsing());
  glUniformMatrix3fv(Uniform(uniform_name), 1, transpose, m.data());
}

/**
 * @name  SetUniform
 * @brief Setup uniform value of type Mat4
 * @param[in] uniform_name  Uniform name variable to set
 * @param[in] m             Matrix data
 * @param[in] transpose     transpose flag (default=false)
 */
void OGLTechnique::SetUniform(const GLchar* uniform_name,
                              const Matrix4<float>& m,
                              GLboolean transpose) {
  assert(IsUsing());
  glUniformMatrix4fv(Uniform(uniform_name), 1, transpose, m.data());
}

/*
 * @name  SetUniform
 * @brief Setup uniform value of type vec3
 * @param[in] uniform_name  Uniform name variable to set
 * @param[in] v             Vector data
 */
void OGLTechnique::SetUniform(const GLchar* uniform_name,
                              const Vector3<float>& v) {
  SetUniform3v(uniform_name, &v.x_);
}
/*
 * @name  SetUniform
 * @brief Setup uniform value of type vec4
 * @param[in] uniform_name  Uniform name variable to set
 * @param[in] v             Vector data
 */
void OGLTechnique::SetUniform(const GLchar* uniform_name,
                              const Vector4<float>& v) {
  SetUniform4v(uniform_name, &v.x_);
}

#pragma mark -
#pragma mark Private
  
/*
 *  @name ExtractShaderType
 *  @fn ShaderType ExtractShaderType(const std::string& filename)
 *  @brief  Extract shader type based on file extension
 *  @param[in]  filename  Shader file
 *  @return Type of shader
 */
OGLTechnique::ShaderType OGLTechnique::ExtractShaderType(const std::string& filename) const {
  // Extract extension
  std::string dir, file, ext;
  CHLib::StringUtil::ExtractDirectory(filename, &dir, &file, &ext);
  if (ext == "vs") {
    return ShaderType::kVertexShader;
  } else if (ext == "gs") {
    return ShaderType::kGeometryShader;
  } else if (ext == "fs") {
    return ShaderType::kFragmentShader;
  }
  return ShaderType::kUnknownShader;
}
  
  
}  // namespace CHLib
