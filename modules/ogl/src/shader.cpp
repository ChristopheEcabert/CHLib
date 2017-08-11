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

#include "oglkit/core/error.hpp"
#include "oglkit/core/string_util.hpp"
#include "oglkit/ogl/shader.hpp"

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#endif

/**
 *  @namespace  OGLKit
 *  @brief      Chris dev space
 */
namespace OGLKit {
  
#pragma mark -
#pragma mark Type definition
  
/**
 *  @struct OGLShaderContext
 *  @brief  OpenGL Program variables
 */
struct OGLShaderContext {
  /** Shader object */
  std::vector<GLuint> shaders;
  /** Program object */
  GLuint program;
  
  /** 
   *  @name OGLShaderContext
   *  @fn OGLShaderContext(void)
   *  @brief  Constructor
   */
  OGLShaderContext(void) : shaders(0, 0), program(0) {
    program = glCreateProgram();
  }
  
  /**
   *  @name ~OGLShaderContext
   *  @fn ~OGLShaderContext(void)
   *  @brief  Destructor
   */
  ~OGLShaderContext(void) {
    // Delete the intermediate shader objects that have been added to the
    // program. The list will only contain something if shaders were compiled
    // but the object itself was destroyed prior to linking.
    for (auto& shader : shaders) {
      glDeleteShader(shader);
    }
    // Release program
    if (program) {
      glDeleteProgram(program);
      program = 0;
    }
  }
  
  /**
   *  @name TypeConverter
   *  @fn static GLenum TypeConverter(const OGLShader::Type& type)
   *  @brief  Convert shader type to opengl format
   *  @param[in]  type  Type of shader
   *  @return Corresponding opengl GLenum
   */
  static GLenum TypeConverter(const OGLShader::Type& type) {
    if (type == OGLShader::Type::kVertex) {
      return GL_VERTEX_SHADER;
    } else if (type == OGLShader::Type::kGeometry) {
      return GL_GEOMETRY_SHADER;
    } else if (type == OGLShader::Type::kFragment) {
      return GL_FRAGMENT_SHADER;
    } else {
      return GL_INVALID_ENUM;
    }
  }
};
  
#pragma mark -
#pragma mark Initialization
  
/*
 *  @name OGLShader
 *  @fn OGLShader(void)
 *  @brief  Consructor
 */
OGLShader::OGLShader(void) {
  // Create context
  ctx_ = new OGLShaderContext();
}

/*
 *  @name ~OGLShader
 *  @fn virtual ~OGLShader(void)
 *  @brief  Destructor
 */
OGLShader::~OGLShader(void) {
  // Release context
  if (ctx_) {
    delete ctx_;
    ctx_ = nullptr;
  }
}

/*
 *  @name Init
 *  @fn virtual int Init(const std::vector<std::string>& paths)
 *  @brief  Initialized OpenGL program
 *  @param[in]  path  List of shader's files to initialize
 *  @return -1 if error, 0 otherwise
 */
int OGLShader::Init(const std::vector<std::string>& paths) {
  int err = 0;
  for (auto& path : paths) {
    err |= this->Add(path);
  }
  return err;
}
  
#pragma mark -
#pragma mark Usage
  
/*
 *  @nme  Add
 *  @fn int Add(const std::string& filename)
 *  @brief  Add a shader to this technique
 *  @param[in]  filename  Path to the file holding shader
 *  @return -1 if error, 0 otherwise
 */
int OGLShader::Add(const std::string& filename) {
  int err = -1;
  // Open file
  std::ifstream in(filename.c_str(), std::ios_base::in|std::ios_base::binary);
  if (in.is_open()) {
    // Read content
    std::stringstream sstream;
    sstream << in.rdbuf();
    // Get type of shader
    Type type = this->ExtractType(filename);
    if (type != Type::kUnknown) {
      err = this->Add(sstream.str(), type);
    } else {
      std::cout << "Unknown shader type" << std::endl;
    }
  } else {
    std::cout << "Unable to open file : " << filename << std::endl;
  }
  return err;
}

/*
 *  @nme  Add
 *  @fn int Add(const std::string& code, const Type& type)
 *  @brief  Add a shader to this technique
 *  @param[in]  code  Code of the shader to add
 *  @param[in]  type  Type of shader it is
 *  @return -1 if error, 0 otherwise
 */
int OGLShader::Add(const std::string& code, const Type& type) {
  int err = -1;
  GLenum gl_type = OGLShaderContext::TypeConverter(type);
  GLuint shader = glCreateShader(gl_type);
  if (shader) {
    // Add to shader list
    ctx_->shaders.push_back(shader);
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
      throw OGLKit::CHError(CHError::kGeneric, msg, FUNC_NAME);
    } else {
      glAttachShader(ctx_->program, shader);
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
int OGLShader::Finalize(void) {
  int err = -1;
  GLint status;
  // Link OpenGL program
  glLinkProgram(ctx_->program);
  glGetProgramiv(ctx_->program, GL_LINK_STATUS, &status);
  if (!status) {
    std::string msg("Program linking failure :\n");
    GLint infoLogLength;
    glGetProgramiv(ctx_->program, GL_INFO_LOG_LENGTH, &infoLogLength);
    char* strInfoLog = new char[infoLogLength + 1];
    glGetProgramInfoLog(ctx_->program, infoLogLength, NULL, strInfoLog);
    msg += strInfoLog;
    delete[] strInfoLog;
    // Show error
    throw OGLKit::CHError(CHError::kGeneric, msg, FUNC_NAME);
  } else {
    // Everything went smooth, release shader object
    for (auto& shader : ctx_->shaders) {
      glDeleteShader(shader);
    }
    ctx_->shaders.clear();
    err = glGetError() == GL_NO_ERROR ? 0 : -1;
  }
  return err;
}

/*
 *  @name
 *  @fn
 *  @brief  Activate technique
 */
void OGLShader::Use(void) const {
  if (ctx_->program) {
    glUseProgram(ctx_->program);
  }
}

/*
 *  @name
 *  @fn
 *  @brief  Deactivate technique
 */
void OGLShader::StopUsing(void) const {
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
bool OGLShader::IsUsing(void) const {
  GLint curr_prog;
  glGetIntegerv(GL_CURRENT_PROGRAM, &curr_prog);
  return (curr_prog == static_cast<GLint>(ctx_->program));
}
  
/*
 *  @name Attrib
 *  @fn GLint Attrib(const GLchar* attrib_name)
 *  @brief  Provide the attribute index for a given name
 *  @param[in]  attrib_name Name of the attribute to look for
 *  @return The uniform index for the given name, as returned
 *          from glGetUniformLocation.
 */
int32_t OGLShader::Attrib(const std::string& attrib_name) const {
  return glGetAttribLocation(ctx_->program, attrib_name.c_str());
}
  
/*
 *  @name Uniform
 *  @fn GLint Uniform(const GLchar* uniform_name)
 *  @brief  Provide uniform reference for a given name
 *  @param[in]  uniform_name  Name of the uniform to look for
 *  @return The uniform index for the given name, as returned
 *          from glGetUniformLocation.
 */
int32_t OGLShader::Uniform(const std::string& uniform_name) const {
  return glGetUniformLocation(ctx_->program, uniform_name.c_str());
}
  
#define ATTRIB_N_UNIFORM_SETTERS(OGL_TYPE, TYPE_PREFIX, TYPE_SUFFIX) \
\
void OGLShader::SetAttrib(const std::string& name, OGL_TYPE v0) const \
{ assert(IsUsing()); glVertexAttrib ## TYPE_PREFIX ## 1 ## TYPE_SUFFIX (Attrib(name), v0); } \
void OGLShader::SetAttrib(const std::string& name, OGL_TYPE v0, OGL_TYPE v1) const \
{ assert(IsUsing()); glVertexAttrib ## TYPE_PREFIX ## 2 ## TYPE_SUFFIX (Attrib(name), v0, v1); } \
void OGLShader::SetAttrib(const std::string& name, OGL_TYPE v0, OGL_TYPE v1, OGL_TYPE v2) const \
{ assert(IsUsing()); glVertexAttrib ## TYPE_PREFIX ## 3 ## TYPE_SUFFIX (Attrib(name), v0, v1, v2); } \
void OGLShader::SetAttrib(const std::string& name, OGL_TYPE v0, OGL_TYPE v1, OGL_TYPE v2, OGL_TYPE v3) const \
{ assert(IsUsing()); glVertexAttrib ## TYPE_PREFIX ## 4 ## TYPE_SUFFIX (Attrib(name), v0, v1, v2, v3); } \
\
void OGLShader::SetAttrib1v(const std::string& name, const OGL_TYPE* v) const \
{ assert(IsUsing()); glVertexAttrib ## TYPE_PREFIX ## 1 ## TYPE_SUFFIX ## v (Attrib(name), v); } \
void OGLShader::SetAttrib2v(const std::string& name, const OGL_TYPE* v) const \
{ assert(IsUsing()); glVertexAttrib ## TYPE_PREFIX ## 2 ## TYPE_SUFFIX ## v (Attrib(name), v); } \
void OGLShader::SetAttrib3v(const std::string& name, const OGL_TYPE* v) const \
{ assert(IsUsing()); glVertexAttrib ## TYPE_PREFIX ## 3 ## TYPE_SUFFIX ## v (Attrib(name), v); } \
void OGLShader::SetAttrib4v(const std::string& name, const OGL_TYPE* v) const \
{ assert(IsUsing()); glVertexAttrib ## TYPE_PREFIX ## 4 ## TYPE_SUFFIX ## v (Attrib(name), v); } \
\
void OGLShader::SetUniform(const std::string& name, OGL_TYPE v0) const \
{ assert(IsUsing()); glUniform1 ## TYPE_SUFFIX (Uniform(name), v0); } \
void OGLShader::SetUniform(const std::string& name, OGL_TYPE v0, OGL_TYPE v1) const \
{ assert(IsUsing()); glUniform2 ## TYPE_SUFFIX (Uniform(name), v0, v1); } \
void OGLShader::SetUniform(const std::string& name, OGL_TYPE v0, OGL_TYPE v1, OGL_TYPE v2) const \
{ assert(IsUsing()); glUniform3 ## TYPE_SUFFIX (Uniform(name), v0, v1, v2); } \
void OGLShader::SetUniform(const std::string& name, OGL_TYPE v0, OGL_TYPE v1, OGL_TYPE v2, OGL_TYPE v3) const \
{ assert(IsUsing()); glUniform4 ## TYPE_SUFFIX (Uniform(name), v0, v1, v2, v3); } \
\
void OGLShader::SetUniform1v(const std::string& name, const OGL_TYPE* v, int32_t count) const \
{ assert(IsUsing()); glUniform1 ## TYPE_SUFFIX ## v (Uniform(name), count, v); } \
void OGLShader::SetUniform2v(const std::string& name, const OGL_TYPE* v, int32_t count) const \
{ assert(IsUsing()); glUniform2 ## TYPE_SUFFIX ## v (Uniform(name), count, v); } \
void OGLShader::SetUniform3v(const std::string& name, const OGL_TYPE* v, int32_t count) const \
{ assert(IsUsing()); glUniform3 ## TYPE_SUFFIX ## v (Uniform(name), count, v); } \
void OGLShader::SetUniform4v(const std::string& name, const OGL_TYPE* v, int32_t count) const \
{ assert(IsUsing()); glUniform4 ## TYPE_SUFFIX ## v (Uniform(name), count, v); }
  
/** Float attribute and uniform setters implementation */
ATTRIB_N_UNIFORM_SETTERS(float, , f);
ATTRIB_N_UNIFORM_SETTERS(int32_t, I, i);
ATTRIB_N_UNIFORM_SETTERS(uint32_t, I, ui);
  
/*
 * @name  SetUniformMat3
 * @brief Setup uniform value of type Mat3 (generic)
 * @param[in] uniform_name  Uniform name variable to set
 * @param[in] v             Pointer to data
 * @param[in] count         count (default=1)
 * @param[in] transpose     transpose flag (default=false)
 */
void OGLShader::SetUniformMat3(const std::string& name,
                                  const float* v,
                                  int32_t count,
                                  uint8_t transpose) const {
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
void OGLShader::SetUniformMat4(const std::string& name,
                                  const float* v,
                                  int32_t count,
                                  uint8_t transpose) const {
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
void OGLShader::SetUniform(const std::string& uniform_name,
                              const Matrix3<float>& m,
                              uint8_t transpose) const {
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
void OGLShader::SetUniform(const std::string& uniform_name,
                              const Matrix4<float>& m,
                              uint8_t transpose) const {
  assert(IsUsing());
  glUniformMatrix4fv(Uniform(uniform_name), 1, transpose, m.data());
}

/*
 * @name  SetUniform
 * @brief Setup uniform value of type vec3
 * @param[in] uniform_name  Uniform name variable to set
 * @param[in] v             Vector data
 */
void OGLShader::SetUniform(const std::string& uniform_name,
                              const Vector3<float>& v) const {
  SetUniform3v(uniform_name, &v.x_);
}
/*
 * @name  SetUniform
 * @brief Setup uniform value of type vec4
 * @param[in] uniform_name  Uniform name variable to set
 * @param[in] v             Vector data
 */
void OGLShader::SetUniform(const std::string& uniform_name,
                              const Vector4<float>& v) const {
  SetUniform4v(uniform_name, &v.x_);
}

#pragma mark -
#pragma mark Private
  
/*
 *  @name ExtractType
 *  @fn Type ExtractType(const std::string& filename)
 *  @brief  Extract shader type based on file extension
 *  @param[in]  filename  Shader file
 *  @return Type of shader
 */
OGLShader::Type OGLShader::ExtractType(const std::string& filename) const {
  // Extract extension
  std::string dir, file, ext;
  OGLKit::StringUtil::ExtractDirectory(filename, &dir, &file, &ext);
  if (ext == "vs") {
    return Type::kVertex;
  } else if (ext == "gs") {
    return Type::kGeometry;
  } else if (ext == "fs") {
    return Type::kFragment;
  }
  return Type::kUnknown;
}
  
  
}  // namespace OGLKit
