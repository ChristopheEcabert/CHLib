/**
 *  @file   shader.hpp
 *  @brief  Basic OpenGL program used to render
 *  @see    http://ogldev.atspace.co.uk
 *
 *  @author Christophe Ecabert
 *  @date   26/08/16
 *  Copyright © 2016 Christophe Ecabert. All rights reserved.
 */

#ifndef __CHLIB_TECHNIQUE__
#define __CHLIB_TECHNIQUE__

#include <string>
#include <vector>
#ifdef __APPLE__
#include <OpenGL/gl3.h>
#endif

#include "chlib/core/library_export.hpp"
#include "chlib/core/math/vector.hpp"
#include "chlib/core/math/matrix.hpp"

/**
 *  @namespace  CHLib
 *  @brief      Chris dev space
 */
namespace CHLib {
  
/**
 *  @class  OGLShader
 *  @brief  Basic OpenGL program used to render
 *  @author Christophe Ecabert
 *  @date   26/08/16
 */
class CHLIB_EXPORTS OGLShader {
 public:
  
#pragma mark -
#pragma mark Type definition
  
  /**
   *  @enum Type
   *  @brief  List of supported shader type
   */
  enum Type {
    /** Unknown */
    kUnknown = -1,
    /** Vertex shader */
    kVertex = GL_VERTEX_SHADER,
    /** Geometry shader */
    kGeometry = GL_GEOMETRY_SHADER,
    /** FRagment shader */
    kFragment = GL_FRAGMENT_SHADER
  };
  
#pragma mark -
#pragma mark Initialization
  
  /**
   *  @name OGLShader
   *  @fn OGLShader(void)
   *  @brief  Consructor
   */
  OGLShader(void);
  
  /**
   *  @name OGLShader
   *  @fn OGLShader(const OGLShader& other) = delete
   *  @brief  Copy Consructor
   */
  OGLShader(const OGLShader& other) = delete;
  
  /**
   *  @name operator=
   *  @fn OGLShader& operator=(const OGLShader& rhs) = delete
   *  @brief  Assignment operator
   *  @param[in]  rhs Object to assign from
   *  @return Newly assigned object
   */
  OGLShader& operator=(const OGLShader& rhs) = delete;
  
  /**
   *  @name ~OGLShader
   *  @fn virtual ~OGLShader(void)
   *  @brief  Destructor
   */
  virtual ~OGLShader(void);
  
  /**
   *  @name Init
   *  @fn virtual int Init(const std::vector<std::string>& paths)
   *  @brief  Initialized OpenGL program
   *  @param[in]  path  List of shader's files to initialize
   *  @return -1 if error, 0 otherwise
   */
  virtual int Init(const std::vector<std::string>& paths);
  
#pragma mark -
#pragma mark Usage
  
  /**
   *  @nme  Add
   *  @fn int Add(const std::string& filename)
   *  @brief  Add a shader to this technique
   *  @param[in]  filename  Path to the file holding shader
   *  @return -1 if error, 0 otherwise
   */
  int Add(const std::string& filename);
  
  /**
   *  @nme  Add
   *  @fn int Add(const std::string& code, const Type& type)
   *  @brief  Add a shader to this technique
   *  @param[in]  code  Code of the shader to add
   *  @param[in]  type  Type of shader it is
   *  @return -1 if error, 0 otherwise
   */
  int Add(const std::string& code, const Type& type);
  
  /**
   *  @name Finalize
   *  @fn int Finalize(void)
   *  @brief  Link OpenGL program
   *  @return -1 if error, 0 othereise
   */
  int Finalize(void);
  
  /**
   *  @name
   *  @fn
   *  @brief  Activate technique
   */
  void Use(void) const;
  
  /**
   *  @name
   *  @fn
   *  @brief  Deactivate technique
   */
  void StopUsing(void) const;
  
#pragma mark -
#pragma mark Accessors
  
  /**
   *  @name IsUsing
   *  @fn bool IsUsing(void)
   *  @brief  Indicate if the current program is being used
   *  @return True if currently used
   */
  bool IsUsing(void) const;
  
  /**
   *  @name Attrib
   *  @fn GLint Attrib(const GLchar* attrib_name)
   *  @brief  Provide the attribute index for a given name
   *  @param[in]  attrib_name Name of the attribute to look for
   *  @return The uniform index for the given name, as returned
   *          from glGetUniformLocation.
   */
  GLint Attrib(const GLchar* attrib_name) const;
  
  /**
   *  @name Uniform
   *  @fn GLint Uniform(const GLchar* uniform_name)
   *  @brief  Provide uniform reference for a given name
   *  @param[in]  uniform_name  Name of the uniform to look for
   *  @return The uniform index for the given name, as returned
   *          from glGetUniformLocation.
   */
  GLint Uniform(const GLchar* uniform_name) const;
  
#define OGL_PROGRAM_ATTRIB_N_UNIFORM_SETTERS(OGL_TYPE) \
void SetAttrib(const GLchar* attrib_name, OGL_TYPE v0) const; \
void SetAttrib(const GLchar* attrib_name, OGL_TYPE v0, OGL_TYPE v1) const; \
void SetAttrib(const GLchar* attrib_name, OGL_TYPE v0, OGL_TYPE v1, OGL_TYPE v2) const; \
void SetAttrib(const GLchar* attrib_name, OGL_TYPE v0, OGL_TYPE v1, OGL_TYPE v2, OGL_TYPE v3) const; \
\
void SetAttrib1v(const GLchar* attrib_name, const OGL_TYPE* v) const; \
void SetAttrib2v(const GLchar* attrib_name, const OGL_TYPE* v) const; \
void SetAttrib3v(const GLchar* attrib_name, const OGL_TYPE* v) const; \
void SetAttrib4v(const GLchar* attrib_name, const OGL_TYPE* v) const; \
\
void SetUniform(const GLchar* uniform_name, const OGL_TYPE v0) const;  \
void SetUniform(const GLchar* uniform_name, const OGL_TYPE v0, const OGL_TYPE v1) const;  \
void SetUniform(const GLchar* uniform_name, const OGL_TYPE v0, const OGL_TYPE v1, const OGL_TYPE v2) const;  \
void SetUniform(const GLchar* uniform_name, const OGL_TYPE v0, const OGL_TYPE v1, const OGL_TYPE v2, const OGL_TYPE v3) const;\
\
void SetUniform1v(const GLchar* uniform_name, const OGL_TYPE* v, GLsizei count=1) const;  \
void SetUniform2v(const GLchar* uniform_name, const OGL_TYPE* v, GLsizei count=1) const;  \
void SetUniform3v(const GLchar* uniform_name, const OGL_TYPE* v, GLsizei count=1) const;  \
void SetUniform4v(const GLchar* uniform_name, const OGL_TYPE* v, GLsizei count=1) const;  \

  /** Float attribute and uniform setters */
  OGL_PROGRAM_ATTRIB_N_UNIFORM_SETTERS(GLfloat);
  /** Int attribute and uniform setters */
  OGL_PROGRAM_ATTRIB_N_UNIFORM_SETTERS(GLint);
  /** Unsigned Int attribute and uniform setters */
  OGL_PROGRAM_ATTRIB_N_UNIFORM_SETTERS(GLuint);
  
  /**
   * @name  SetUniformMat3
   * @brief Setup uniform value of type Mat3 (generic)
   * @param[in] uniform_name  Uniform name variable to set
   * @param[in] v             Pointer to data
   * @param[in] count         count (default=1)
   * @param[in] transpose     transpose flag (default=false)
   */
  void SetUniformMat3(const GLchar* uniform_name,
                      const GLfloat* v,
                      GLsizei count=1,
                      GLboolean transpose = GL_FALSE) const;
  /**
   * @name  SetUniformMat4
   * @brief Setup uniform value of type Mat4 (generic)
   * @param[in] uniform_name  Uniform name variable to set
   * @param[in] v             Pointer to data
   * @param[in] count         count (default=1)
   * @param[in] transpose     transpose flag (default=false)
   */
  void SetUniformMat4(const GLchar* uniform_name,
                      const GLfloat* v,
                      GLsizei count = 1,
                      GLboolean transpose=GL_FALSE) const;

  /**
   * @name  SetUniform
   * @brief Setup uniform value of type Mat3
   * @param[in] uniform_name  Uniform name variable to set
   * @param[in] m             Matrix data
   * @param[in] transpose     transpose flag (default=false)
   */
  void SetUniform(const GLchar* uniform_name,
                  const Matrix3<float>& m,
                  GLboolean transpose=GL_FALSE) const;
  
  /**
   * @name  SetUniform
   * @brief Setup uniform value of type Mat4
   * @param[in] uniform_name  Uniform name variable to set
   * @param[in] m             Matrix data
   * @param[in] transpose     transpose flag (default=false)
   */
  void SetUniform(const GLchar* uniform_name,
                  const Matrix4<float>& m,
                  GLboolean transpose=GL_FALSE) const;
  
  /**
   * @name  SetUniform
   * @brief Setup uniform value of type vec3
   * @param[in] uniform_name  Uniform name variable to set
   * @param[in] v             Vector data
   */
  void SetUniform(const GLchar* uniform_name,
                  const Vector3<float>& v) const;
  /**
   * @name  SetUniform
   * @brief Setup uniform value of type vec4
   * @param[in] uniform_name  Uniform name variable to set
   * @param[in] v             Vector data
   */
  void SetUniform(const GLchar* uniform_name,
                  const Vector4<float>& v) const;
  
  
#pragma mark -
#pragma mark Private
 private:
  
  /**
   *  @name ExtractType
   *  @fn Type ExtractType(const std::string& filename)
   *  @brief  Extract shader type based on file extension
   *  @param[in]  filename  Shader file
   *  @return Type of shader
   */
  Type ExtractType(const std::string& filename) const;
  
  /** Shader object list */
  std::vector<GLuint> shaders_;
  /** Program */
  GLuint program_;
};
  
}  // namespace CHLib


#endif /* __CHLIB_OGLShader__ */
