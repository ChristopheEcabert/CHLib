/**
 *  @file   image_loader.cpp
 *  @brief  Example to show how to use image class
 *
 *  @author Christophe Ecabert
 *  @date   05.03.17
 *    Copyright © 2017 Christophe Ecabert. All rights reserved.
 */

#include <iostream>

#include "oglkit/core/cmd_parser.hpp"
#include "oglkit/core/string_util.hpp"
#include "oglkit/io/image_factory.hpp"

int main(const int argc, const char** argv) {
  // Define argument needed
  OGLKit::CmdLineParser parser;
  parser.AddArgument("-i",
                     OGLKit::CmdLineParser::ArgState::kNeeded,
                     "Input image");
  // Parse
  int err = parser.ParseCmdLine(argc, argv);
  if (!err) {
    std::string imagepath;
    parser.HasArgument("-i", &imagepath);

    // Load image based on type
    std::string dir, file, ext;
    OGLKit::StringUtil::ExtractDirectory(imagepath, &dir, &file, &ext);
    OGLKit::Image* image = OGLKit::ImageFactory::Get().CreateByExtension(ext);
    // Save input
    if (image && !image->Load(imagepath)) {
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
