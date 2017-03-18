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
#include "chlib/io/image_loader.hpp"

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
    err = CHLib::ImageLoader::Load(imagepath, &image);
    // Save input
    if (!err) {
      std::string dir, file, ext;
      CHLib::StringUtil::ExtractDirectory(imagepath, &dir, &file, &ext);
      std::string f = (dir.empty() ?
                       file + "_save" :
                       dir + "/" + file + "_save");
      image->Save(f);
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
