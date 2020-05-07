// Copyright (c) 2020 [Dev Wadhwa]. All rights reserved.

#include <cinder/app/App.h>
#include <cinder/app/RendererGl.h>

#include "my_app.h"


using cinder::app::App;
using cinder::app::RendererGl;


namespace myapp {

const int kSamples = 8;
const int kDimension = 800;

void SetUp(App::Settings* settings) {
  settings->setWindowSize(kDimension, kDimension);
  settings->setTitle("Prison Break - devjw2");
  //settings->setConsoleWindowEnabled();
}

}  // namespace myapp


// This is a macro that runs the application.
CINDER_APP(myapp::MyApp,
           RendererGl(RendererGl::Options().msaa(myapp::kSamples)),
           myapp::SetUp)
