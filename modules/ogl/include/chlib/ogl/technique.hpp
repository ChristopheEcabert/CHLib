/**
 *  @file   technique.hpp
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
 *  @class  OGLTechnique
 *  @brief  Basic OpenGL program used to render
 *  @author Christophe Ecabert
 *  @date   26/08/16
 */
class CHLIB_EXPORTS OGLTechnique {
 public:
  
#pragma mark -
#pragma mark Type definition
  
  /**
   *  @enum ShaderType
   *  @brief  List of supported shader type
   */
  enum ShaderType {
    /** Unknown */
    kUnknownShader = -1,
    /** Vertex shader */
    kVertexShader = GL_VERTEX_SHADER,
    /** Geometry shader */
    kGeometryShader = GL_GEOMETRY_SHADER,
    /** FRagment shader */
    kFragmentShader = GL_FRAGMENT_SHADER
  };
  
#pragma mark -
#pragma mark Initialization
  
  /**
   *  @name OGLTechnique
   *  @fn OGLTechnique(void)
   *  @brief  Consructor
   */
  OGLTechnique(void);
  
  /**
   *  @name OGLTechnique
   *  @fn OGLTechnique(const OGLTechnique& other) = delete
   *  @brief  Copy Consructor
   */
  OGLTechnique(const OGLTechnique& other) = delete;
  
  /**
   *  @name operator=
   *  @fn OGLTechnique& operator=(const OGLTechnique& rhs) = delete
   *  @brief  Assignment operator
   *  @param[in]  rhs Object to assign from
   *  @return Newly assigned object
   */
  OGLTechnique& operator=(const OGLTechnique& rhs) = delete;
  
  /**
   *  @name ~OGLTechnique
   *  @fn virtual ~OGLTechnique(void)
   *  @brief  Destructor
   */
  virtual ~OGLTechnique(void);
  
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
   *  @nme  AddShader
   *  @fn int AddShader(const std::string& filename)
   *  @brief  Add a shader to this technique
   *  @param[in]  filename  Path to the file holding shader
   *  @return -1 if error, 0 otherwise
   */
  int AddShader(const std::string& filename);
  
  /**
   *  @nme  AddShader
   *  @fn int AddShader(const std::string& code, const ShaderType& type)
   *  @brief  Add a shader to this technique
   *  @param[in]  code  Code of the shader to add
   *  @param[in]  type  Type of shader it is
   *  @return -1 if error, 0 otherwise
   */
  int AddShader(const std::string& code, const ShaderType& type);
  
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
void SetAttrib(const GLchar* attrib_name, OGL_TYPE v0); \
void SetAttrib(const GLchar* attrib_name, OGL_TYPE v0, OGL_TYPE v1); \
void SetAttrib(const GLchar* attrib_name, OGL_TYPE v0, OGL_TYPE v1, OGL_TYPE v2); \
void SetAttrib(const GLchar* attrib_name, OGL_TYPE v0, OGL_TYPE v1, OGL_TYPE v2, OGL_TYPE v3); \
\
void SetAttrib1v(const GLchar* attrib_name, const OGL_TYPE* v); \
void SetAttrib2v(const GLchar* attrib_name, const OGL_TYPE* v); \
void SetAttrib3v(const GLchar* attrib_name, const OGL_TYPE* v); \
void SetAttrib4v(const GLchar* attrib_name, const OGL_TYPE* v); \
\
void SetUniform(const GLchar* uniform_name, const OGL_TYPE v0);  \
void SetUniform(const GLchar* uniform_name, const OGL_TYPE v0, const OGL_TYPE v1);  \
void SetUniform(const GLchar* uniform_name, const OGL_TYPE v0, const OGL_TYPE v1, const OGL_TYPE v2);  \
void SetUniform(const GLchar* uniform_name, const OGL_TYPE v0, const OGL_TYPE v1, const OGL_TYPE v2, const OGL_TYPE v3);\
\
void SetUniform1v(const GLchar* uniform_name, const OGL_TYPE* v, GLsizei count=1);  \
void SetUniform2v(const GLchar* uniform_name, const OGL_TYPE* v, GLsizei count=1);  \
void SetUniform3v(const GLchar* uniform_name, const OGL_TYPE* v, GLsizei count=1);  \
void SetUniform4v(const GLchar* uniform_name, const OGL_TYPE* v, GLsizei count=1);  \

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
                      GLboolean transpose = GL_FALSE);
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
                      GLboolean transpose=GL_FALSE);

  /**
   * @name  SetUniform
   * @brief Setup uniform value of type Mat3
   * @param[in] uniform_name  Uniform name variable to set
   * @param[in] m             Matrix data
   * @param[in] transpose     transpose flag (default=false)
   */
  void SetUniform(const GLchar* uniform_name,
                  const Matrix3<float>& m,
                  GLboolean transpose=GL_FALSE);
  
  /**
   * @name  SetUniform
   * @brief Setup uniform value of type Mat4
   * @param[in] uniform_name  Uniform name variable to set
   * @param[in] m             Matrix data
   * @param[in] transpose     transpose flag (default=false)
   */
  void SetUniform(const GLchar* uniform_name,
                  const Matrix4<float>& m,
                  GLboolean transpose=GL_FALSE);
  
  /**
   * @name  SetUniform
   * @brief Setup uniform value of type vec3
   * @param[in] uniform_name  Uniform name variable to set
   * @param[in] v             Vector data
   */
  void SetUniform(const GLchar* uniform_name,
                  const Vector3<float>& v);
  /**
   * @name  SetUniform
   * @brief Setup uniform value of type vec4
   * @param[in] uniform_name  Uniform name variable to set
   * @param[in] v             Vector data
   */
  void SetUniform(const GLchar* uniform_name,
                  const Vector4<float>& v);
  
  
#pragma mark -
#pragma mark Private
 private:
  
  /**
   *  @name ExtractShaderType
   *  @fn ShaderType ExtractShaderType(const std::string& filename)
   *  @brief  Extract shader type based on file extension
   *  @param[in]  filename  Shader file
   *  @return Type of shader
   */
  ShaderType ExtractShaderType(const std::string& filename) const;
  
  /** Shader object list */
  std::vector<GLuint> shaders_;
  /** Program */
  GLuint program_;
};
  
}  // namespace CHLib


#endif /* __CHLIB_OGLTechnique__ */
