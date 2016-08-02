/**
 *  @file   mesh.hpp
 *  @brief  3D Mesh container
 *
 *  @author Christophe Ecabert
 *  @date   02/08/16
 *  Copyright © 2016 Christophe Ecabert. All rights reserved.
 */

#ifndef __CHLIB_MESH__
#define __CHLIB_MESH__

#include <vector>

#include "chlib/core/library_export.hpp"
#include "chlib/core/math/vector.hpp"
#include "chlib/geometry/aabb.hpp"

/**
 *  @namespace  CHLib
 *  @brief      Chris dev space
 */
namespace CHLib {

/**
 *  @class  Mesh
 *  @brief  3D Mesh container
 *  @author Christophe Ecabert
 *  @date   02/08/16
 */
template<typename T>
class CHLIB_EXPORTS Mesh {

 public:

#pragma mark - 
#pragma mark Type definition

  /** Vertex */
  using Vertex = CHLib::Vector3<T>;
  /** Edge */
  using Edge = CHLib::Vector3<T>;
  /** Normal */
  using Normal = CHLib::Vector3<T>;
  /** Texture coordinate */
  using TCoord = CHLib::Vector2<T>;
  /** Vertex color */
  using Color = CHLib::Vector4<T>;
  /** Tangente space */
  using Tengent = CHLib::Vector3<T>;
  /** Triangle */
  using Triangle = CHLib::Vector3<int>;

#pragma mark -
#pragma mark Initialization

  /**
   *  @name Mesh
   *  @fn Mesh(void)
   *  @brief  Constructor
   */
  Mesh(void);

  /**
   *  @name Mesh
   *  @fn Mesh(const std::string& filename)
   *  @brief  Load mesh from supported file :
   *            .obj, .ply, .tri
   *  @param[in]  filename  Path to the mesh file
   */
  Mesh(const std::string& filename);

  /**
   *  @name Mesh
   *  @fn Mesh(const Mesh<T>& other) = delete
   *  @brief  Copy constructor
   *  @param[in]  other Mesh to copy from
   */
  Mesh(const Mesh<T>& other) = delete;

  /**
   *  @name operator=
   *  @fn Mesh& operator=(const Mesh& rhs) = delete
   *  @brief  Assignment operator
   *  @param[in]  rhs   Mesh to assign from
   */
  Mesh& operator=(const Mesh<T>& rhs) = delete;

  /**
   *  @name ~Mesh
   *  @fn ~Mesh(void)
   *  @brief  Destructor
   */
  ~Mesh(void);

  /**
   *  @name Load
   *  @fn int Load(const std::string& filename, const LTS5::OGLProgram& program)
   *  @brief  Load mesh from supported file : .obj, .ply, .tri
   *  @param[in]  filename  Path to the mesh file
   *  @return -1 if error, 0 otherwise
   */
  int Load(const std::string& filename);

  /**
   *  @name Save
   *  @fn int Save(const std::string& filename)
   *  @brief  Save mesh to supported file format: .ply/.obj
   *  @return -1 if error, 0 otherwise
   */
  int Save(const std::string& filename);

  /**
   *  @name BuildConnectivity
   *  @fn void BuildConnectivity(void)
   *  @brief  Construct vertex connectivity (vertex connection) used later
   *          in normal computation
   */
  void BuildConnectivity(void);

#pragma mark -
#pragma mark Usage

  /**
   *  @name ComputeVertexNormal
   *  @fn void ComputeVertexNormal(void)
   *  @brief  Compute normal for each vertex in the object
   */
  void ComputeVertexNormal(void);

  /**
   *  @name ComputeBoundingBox
   *  @fn void ComputeBoundingBox(void)
   *  @brief  Compute the bounding box of the mesh
   */
  void ComputeBoundingBox(void);

#pragma mark -
#pragma mark Accessors

  /**
   *  @name get_vertex
   *  @fn const std::vector<Vertex>& get_vertex(void) const
   *  @brief Give reference to internal vertex storage, can not be modified.
   *  @return Vertex array
   */
  const std::vector<Vertex>& get_vertex(void) const {
    return vertex_;
  }

  /**
   *  @name get_vertex
   *  @fn std::vector<Vertex>& get_vertex(void)
   *  @brief Give reference to internal vertex storage.
   *  @return Vertex array
   */
  std::vector<Vertex>& get_vertex(void) {
    return vertex_;
  }

  /**
   *  @name get_normal
   *  @fn const std::vector<Normal>& get_normal(void) const
   *  @brief Give reference to internal normal storage, can not be modified.
   *  @return Normal array
   */
  const std::vector<Normal>& get_normal(void) const {
    return normal_;
  }

  /**
   *  @name get_normal
   *  @fn std::vector<Normal>& get_normal(void)
   *  @brief Give reference to internal normal storage.
   *  @return Normal array
   */
  std::vector<Normal>& get_normal(void) {
    return normal_;
  }

  /**
   *  @name get_tex_coord
   *  @fn const std::vector<TCoord>& get_tex_coord(void) const
   *  @brief  Give reference to internal texture coordinate storage, can not be
   *          modified.
   *  @return Texture coordinate array
   */
  const std::vector<TCoord>& get_tex_coord(void) const {
    return tex_coord_;
  }

  /**
   *  @name get_tex_coord
   *  @fn std::vector<TCoord>& get_tex_coord(void)
   *  @brief  Give reference to internal texture coordinate storage.
   *  @return Texture coordinate array
   */
  std::vector<TCoord>& get_tex_coord(void) {
    return tex_coord_;
  }

  /**
   *  @name get_vertex_color
   *  @fn const std::vector<Color>& get_vertex_color(void) const
   *  @brief  Give reference to internal vertex color storage, can not be
   *          modified.
   *  @return Vertex color array
   */
  const std::vector<Color>& get_vertex_color(void) const {
    return vertex_color_;
  }

  /**
   *  @name get_vertex_color
   *  @fn std::vector<Color>& get_vertex_color(void)
   *  @brief  Give reference to internal vertex color storage.
   *  @return Vertex color array
   */
  std::vector<Color>& get_vertex_color(void) {
    return vertex_color_;
  }

  /**
   *  @name get_triangle
   *  @fn const std::vector<Triangle>& get_triangle(void) const
   *  @brief  Give reference to internal triangulation storage, can not be
   *          modified.
   *  @return Triangle array
   */
  const std::vector<Triangle>& get_triangle(void) const {
    return tri_;
  }

  /**
   *  @name get_triangle
   *  @fn std::vector<Triangle>& get_triangle(void)
   *  @brief  Give reference to internal triangulation storage, can not be
   *          modified.
   *  @return Triangle array
   */
  std::vector<Triangle>& get_triangle(void) {
    return tri_;
  }

  /**
   *  @name bbox
   *  @fn const AABB<T>& bbox(void) const
   *  @brief  Getter for the bounding box
   */
  const AABB<T>& bbox(void) const {
    return bbox_;
  }

#pragma mark -
#pragma mark Private
 private:

  /**
   *  @enum FileExt
   *  @brief  Type of possible mesh extension file
   */
  enum FileExt {
    /** Undefined */
    kUndef,
    /** .obj */
    kObj,
    /** .ply */
    kPly,
    /** .tri */
    kTri
  };

  /** Vertex */
  std::vector<Vertex> vertex_;
  /** Normal */
  std::vector<Normal> normal_;
  /** Texture coordinate */
  std::vector<TCoord> tex_coord_;
  /** Vertex color */
  std::vector<Color> vertex_color_;
  /** Triangulation */
  std::vector<Triangle> tri_;
  /** Connectivity - vertex interconnection */
  std::vector<std::vector<int>> vertex_con_;
  /** Boundary box, {x_min, x_max, y_min, y_max, z_min, z_max, } */
  AABB<T> bbox_;
  /** Wether or not the bounding box has been computed already or not */
  bool bbox_is_computed_;

  /**
   *  @name HashExt
   *  @fn FileExt HashExt(const std::string& ext)
   *  @brief  Provide the type of extension
   *  @param[in]  ext Name of the extension
   *  @return Hash of the given extension if know by the object
   */
  FileExt HashExt(const std::string& ext);

  /**
   *  @name LoadOBJ
   *  @fn int LoadOBJ(const std::string& path)
   *  @brief  Load mesh from .obj file
   *  @param[in]  path  Path to .obj file
   *  @return -1 if error, 0 otherwise
   */
  int LoadOBJ(const std::string& path);

  /**
   *  @name SaveOBJ
   *  @fn int SaveOBJ(const std::string path) const
   *  @brief SAve mesh to a .obj file
   *  @param[in]  path  Path to .obj file
   *  @return -1 if error, 0 otherwise
   */
  int SaveOBJ(const std::string& path);

  /**
   *  @name LoadPLY
   *  @fn int LoadPLY(const std::string path)
   *  @brief  Load mesh from .ply file
   *  @param[in]  path  Path to .ply file
   *  @return -1 if error, 0 otherwise
   */
  int LoadPLY(const std::string& path);

  /**
   *  @name SavePLY
   *  @fn int SavePLY(const std::string path) const
   *  @brief SAve mesh to a .ply file
   *  @param[in]  path  Path to .ply file
   *  @return -1 if error, 0 otherwise
   */
  int SavePLY(const std::string& path) const;

  /**
   *  @name LoadTri
   *  @fn int LoadTri(const std::string path)
   *  @brief  Load mesh triangulation from .tri file
   *  @param[in]  path  Path to .tri file
   *  @return -1 if error, 0 otherwise
   */
  int LoadTri(const std::string& path);
  
};

}  // namespace CHLib


#endif /* __CHLIB_MESH__ */
