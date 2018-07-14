// Copyright 2018 Aubin REBILLAT
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//    http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "display_delegate.h"

#include "string.h"

#include <iostream>

DemoDisplayDelegate::DemoDisplayDelegate(int width, int height)
  : width_(width), height_(height) {
  EGLint egl_major, egl_minor;
}

DemoDisplayDelegate::~DemoDisplayDelegate() {
}

EGLNativeDisplayType DemoDisplayDelegate::CreateNativeDisplay() {
  x_display_ = XOpenDisplay(NULL);
  return x_display_;
}

void DemoDisplayDelegate::ReleaseNativeDisplay() {
}

EGLNativeWindowType DemoDisplayDelegate::CreateNativeWindow() {
  int num_visuals, screen;
  unsigned long mask;
  Window root;
  XSetWindowAttributes attr;
  XVisualInfo *visInfo, visTemplate;
  XSizeHints sizehints;
  EGLint num_configs, visual_id;

  memset(&attr, 0, sizeof (XSetWindowAttributes));
  attr.background_pixel = 0;
  attr.border_pixel = 0;
  attr.backing_store = Always;
  screen = DefaultScreen(x_display_);
  root = RootWindow(x_display_, screen);
  x_window_ = XCreateWindow(
    x_display_, root,
    0 /* x */, 0 /* y */,
    width_, height_,
    0 /* border width */,
    CopyFromParent /* depth */,
    InputOutput /* class */,
    CopyFromParent /* visual */,
    CWBackPixmap | CWBitGravity /* mask */,
    &attr);
  XMapWindow(x_display_, x_window_);
  XFlush(x_display_);

  return x_window_;
}

void DemoDisplayDelegate::ReleaseNativeWindow() {
}

bool DemoDisplayDelegate::Resize(int width, int height, float scale_factor) {
  XResizeWindow(x_display_, x_window_, width, height);
}

void DemoDisplayDelegate::GetSize(int* width, int* height) {
  *width = width_;
  *height = height_;
}

char *DemoDisplayDelegate::EGLLibraryName() {
#ifdef USE_NVIDIA
  return "libEGL_nvidia.so.0";
#else
  return "libEGL.so.1";
#endif
}

char *DemoDisplayDelegate::GLESLibraryName() {
#ifdef USE_NVIDIA
  return "libGLESv2_nvidia.so.367.57";
#else
  return "libGLESv2.so.2";
#endif
}
