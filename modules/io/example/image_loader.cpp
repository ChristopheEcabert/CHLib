/**
 *  @file   image_loader.cpp
 *  @brief  Example to show how to use image class
 *
 *  @author Christophe Ecabert
 *  @date   05.03.17
 *    Copyright © 2017 Christophe Ecabert. All rights reserved.
 */

#include <iostream>

#include "chlib/core/cmd_parser.hpp"
#include "chlib/core/string_util.hpp"
#include "chlib/io/jpeg_image.hpp"
#include "chlib/io/tga_image.hpp"

int main(const int argc, const char** argv) {
  // Define argument needed
  CHLib::CmdLineParser parser;
  parser.AddArgument("-i",
                     CHLib::CmdLineParser::ArgState::kNeeded,
                     "Input image");
  // Parse
  int err = parser.ParseCmdLine(argc, argv);
  if (!err) {
    std::string imagepath;
    parser.HasArgument("-i", &imagepath);

    // Load image based on type
    CHLib::Image* image;
    std::string dir, file, ext;
    CHLib::StringUtil::ExtractDirectory(imagepath, &dir, &file, &ext);
    // Init based on extension type
    if (ext == "jpg") {
      image = new CHLib::JPEGImage();
    } else if (ext == "tga") {
      image = new CHLib::TGAImage();
    } else {
      std::cout << "Unknown image type" << std::endl;
      err = -1;
    }
    
    // Load + Save input
    if (!err) {
      err = image->Load(imagepath);
      if (!err) {
        std::string f = (dir.empty() ?
                         file + "_save" :
                         dir + "/" + file + "_save");
        image->Save(f);
      }
    }
    std::cout << "Done : " << (!err ? "Success" : "Fail") << std::endl;
    if (image) {
      delete image;
    }
  } else {
    std::cout << "Unable to parse cmd line" << std::endl;
  }
  return err;
}
