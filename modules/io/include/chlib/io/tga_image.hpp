/**
 *  @file   tga_image.hpp
 *  @brief  TGA Image object
 *  @ingroup io
 *
 *  @author Christophe Ecabert
 *  @date   05.03.17
 *  Copyright © 2017 Christophe Ecabert. All rights reserved.
 */

#ifndef __CHLIB_TGA_IMAGE__
#define __CHLIB_TGA_IMAGE__

#include <istream>
#include <ostream>

#include "chlib/io/image.hpp"

/**
 *  @namespace  CHLib
 *  @brief      Chris dev space
 */
namespace CHLib {
  
/**
 *  @class  TGAImage
 *  @brief  TGA Image object
 *  @author Christophe Ecabert
 *  @date   05.03.17
 *  @ingroup io
 */
class TGAImage : public Image {
 public:
  
#pragma mark -
#pragma mark Type Definition
  
  /**
   *  @struct TGAColorMapSpec
   *  @brief  Color map specification
   */
  struct TGAColorMapSpec {
    /** Index of first color map entry that is included in the file */
    unsigned short index_first_entry;
    /** Number of entries of the color map that are included in the file */
    unsigned short n_entry;
    /** number of bits per pixel */
    unsigned char n_bit_per_pixel;
    
    /**
     *  @name TGAColorMapSpec
     *  @fn TGAColorMapSpec(void)
     *  @brief  Contructor
     */
    TGAColorMapSpec(void) : index_first_entry(0),
                            n_entry(0),
                            n_bit_per_pixel(0){
    }
    
    /**
     *  @name operator>>
     *  @fn friend std::istream& operator>>(std::istream& in,
                                            TGAColorMapSpec& spec)
     *  @brief  Input
     *  @param[in]  in        Input binary stream
     *  @param[in,out]  spec  Color map header to fill
     */
    friend std::istream& operator>>(std::istream& in, TGAColorMapSpec& spec) {
      if (in.good()) {
        in.read(reinterpret_cast<char*>(&spec.index_first_entry),
                sizeof(index_first_entry));
        in.read(reinterpret_cast<char*>(&spec.n_entry),
                sizeof(n_entry));
        in.read(reinterpret_cast<char*>(&spec.n_bit_per_pixel),
                sizeof(n_bit_per_pixel));
      }
      return in;
    }
    
    /**
     *  @name operator<<
     *  @fn friend std::ostream& operator<<(std::ostream& out,
                                            TGAColorMapSpec& spec)
     *  @brief  Write
     *  @param[in]  out       Output binary stream
     *  @param[in,out]  spec  Color map header to fill
     */
    friend std::ostream& operator<<(std::ostream& out,
                                    const TGAColorMapSpec& spec) {
      if (out.good()) {
        out.write(reinterpret_cast<const char*>(&spec.index_first_entry),
                  sizeof(index_first_entry));
        out.write(reinterpret_cast<const char*>(&spec.n_entry),
                  sizeof(n_entry));
        out.write(reinterpret_cast<const char*>(&spec.n_bit_per_pixel),
                  sizeof(n_bit_per_pixel));
      }
      return out;
    }
  };
  
  /**
   *  @struct TGAImageSpec
   *  @brief  Image specification
   */
  struct TGAImageSpec {
    /** X origin */
    unsigned short x_origin;
    /** Y origin */
    unsigned short y_origin;
    /** Image width */
    unsigned short width;
    /** Image height */
    unsigned short height;
    /** Pixel depth */
    unsigned char pixel_depth;
    /** Image descriptor - bits 3-0 give the alpha channel depth,
     bits 5-4 give direction */
    unsigned char image_descriptor;
    
    /**
     *  @name operator>>
     *  @fn friend std::istream& operator>>(std::istream& in,
                                            TGAImageSpec& spec)
     *  @brief  Input
     *  @param[in]  in    Input binary stream
     *  @param[out] spec  Image spec to fill
     */
    friend std::istream& operator>>(std::istream& in, TGAImageSpec& spec) {
      if (in.good()) {
        in.read(reinterpret_cast<char*>(&spec.x_origin), sizeof(x_origin));
        in.read(reinterpret_cast<char*>(&spec.y_origin), sizeof(y_origin));
        in.read(reinterpret_cast<char*>(&spec.width), sizeof(width));
        in.read(reinterpret_cast<char*>(&spec.height), sizeof(height));
        in.read(reinterpret_cast<char*>(&spec.pixel_depth),
                sizeof(pixel_depth));
        in.read(reinterpret_cast<char*>(&spec.image_descriptor),
                sizeof(image_descriptor));
      }
      return in;
    }
    
    /**
     *  @name operator<<
     *  @fn friend std::ostream& operator<<(std::ostream& out,
                                            TGAImageSpec& spec)
     *  @brief  Write
     *  @param[in]  out  Input binary stream
     *  @param[in]  spec Image spec to write
     */
    friend std::ostream& operator<<(std::ostream& out,
                                    const TGAImageSpec& spec) {
      if (out.good()) {
        out.write(reinterpret_cast<const char*>(&spec.x_origin),
                  sizeof(x_origin));
        out.write(reinterpret_cast<const char*>(&spec.y_origin),
                  sizeof(y_origin));
        out.write(reinterpret_cast<const char*>(&spec.width),
                  sizeof(width));
        out.write(reinterpret_cast<const char*>(&spec.height),
                  sizeof(height));
        out.write(reinterpret_cast<const char*>(&spec.pixel_depth),
                  sizeof(pixel_depth));
        out.write(reinterpret_cast<const char*>(&spec.image_descriptor),
                  sizeof(image_descriptor));
      }
      return out;
    }
  };
  
  /**
   *  @struct TGAHeader
   *  @brief  TGA file header
   */
  struct TGAHeader {
    /** ID length	Length of the image ID field */
    unsigned char id_length;
    /** Color map type - 0/1 */
    unsigned char color_map_type;
    /** Image type - compression and color type */
    unsigned char image_type;
    /** Color map specification */
    TGAColorMapSpec color_map_spec;
    /** Image specification */
    TGAImageSpec image_spec;
    
    /**
     *  @name operator>>
     *  @fn friend std::istream& operator>>(std::istream& in,
                                            TGAHeader& header)
     *  @brief  Input
     *  @param[in]  in  Input binary stream
     *  @param[in,out]  header Image spec to fill
     */
    friend std::istream& operator>>(std::istream& in, TGAHeader& header) {
      if (in.good()) {
        // Read data
        in.read(reinterpret_cast<char*>(&header.id_length), sizeof(id_length));
        in.read(reinterpret_cast<char*>(&header.color_map_type),
                sizeof(color_map_type));
        in.read(reinterpret_cast<char*>(&header.image_type),
                sizeof(image_type));
        // Color map spec + image spec
        in >> header.color_map_spec >> header.image_spec;
      }
      return in;
    }
    
    /**
     *  @name operator<<
     *  @fn friend std::ostream& operator<<(std::ostream& out,
                                            TGAHeader& header)
     *  @brief  Write
     *  @param[in]  out         Output binary stream
     *  @param[in,out] header   Image spec to fill
     */
    friend std::ostream& operator<<(std::ostream& out, const TGAHeader& header){
      if (out.good()) {
        // Read data
        out.write(reinterpret_cast<const char*>(&header.id_length),
                  sizeof(id_length));
        out.write(reinterpret_cast<const char*>(&header.color_map_type),
                  sizeof(color_map_type));
        out.write(reinterpret_cast<const char*>(&header.image_type),
                  sizeof(image_type));
        // Color map spec + image spec
        out << header.color_map_spec;
        out << header.image_spec;
      }
      return out;
    }
  };
  
#pragma mark -
#pragma mark Initialization
  
  /**
   *  @name TGAImage
   *  @fn TGAImage(void)
   *  @brief  Constructor
   */
  TGAImage(void);
  
  /**
   *  @name TGAImage
   *  @fn TGAImage(const TGAImage& other) = delete
   *  @brief  Copy Constructor
   *  @param[in]  other Object to copy
   */
  TGAImage(const TGAImage& other) = delete;
  
  /**
   *  @name operator=
   *  @fn TGAImage& operator=(const TGAImage& rhs) = delete
   *  @brief  Assignment operator
   *  @param[in]  rhs Object to assign form
   *  @return Newly assign object
   */
  TGAImage& operator=(const TGAImage& rhs) = delete;
  
  /**
   *  @name ~TGAImage
   *  @fn ~TGAImage(void)
   *  @brief  Destructor
   */
  ~TGAImage(void);
  
  /**
   *  @name Load
   *  @fn int Load(const std::string& filename)
   *  @brief  Load image from dist
   *  @param[in]  filename  Path to ressource on the disk
   *  @return -1 if error, 0 otherwise
   */
  int Load(const std::string& filename);
  
  /**
   *  @name Load
   *  @fn int Load(std::istream& stream)
   *  @brief  Load image from dist
   *  @param[in]  stream  Binary stream from where to load the ressource
   *  @return -1 if error, 0 otherwise
   */
  int Load(std::istream& stream);
  
  /**
   *  @name Save
   *  @fn int Save(const std::string& filename) const
   *  @brief  Save image to dist
   *  @param[in]  filename  Path to ressource on the disk
   *  @return -1 if error, 0 otherwise
   */
  int Save(const std::string& filename) const;
  
  /**
   *  @name Save
   *  @fn int Save(std::ostream& stream) const
   *  @brief  Load image to dist
   *  @param[in]  stream  Binary stream to where to save the ressource
   *  @return -1 if error, 0 otherwise
   */
  int Save(std::ostream& stream) const;
  
#pragma mark -
#pragma mark Private
 private:
  /** TGA header */
  TGAHeader header_;
};
}  // namespace CHLib
#endif /* __CHLIB_TGA_IMAGE__ */
