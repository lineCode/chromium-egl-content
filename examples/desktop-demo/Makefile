# Copyright 2018 Aubin REBILLAT
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#    http:://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

TOPDIR                 ?= ../..
BUILD_OUTPUT_DIRECTORY ?= examples/desktop-demo
OUTPUT_DIRECTORY        = $(TOPDIR)/$(BUILD_OUTPUT_DIRECTORY)/eglcontent-desktop-demo

SOURCES   = application.cc display_delegate.cc main_delegate.cc
SOURCES  += browser_delegate.cc command_line_interface.cc main.cc
OBJS      = $(SOURCES:.cc=.o)
C_FLAGS   = $(CFLAGS) -std=c++11 -I$(TOPDIR)/$(BUILD_OUTPUT_DIRECTORY) -g -ggdb -Wall -Werror
LD_FLAGS  = $(LDFLAGS) -L$(TOPDIR)/$(BUILD_OUTPUT_DIRECTORY)
LD_FLAGS += -legl_content_lib -lEGL -lGLESv2 -lX11 -lpthread
TARGET    = egl_content_demo

all: $(OUTPUT_DIRECTORY) $(OBJS) $(TARGET)

$(OUTPUT_DIRECTORY):
	mkdir $@

$(TARGET): $(OBJS)
	cd $(OUTPUT_DIRECTORY) && $(CXX) $(OBJS) $(LD_FLAGS) \
		-o $(TOPDIR)/$(BUILD_OUTPUT_DIRECTORY)/$(TARGET)

%.o : %.cc
	$(CXX) $(C_FLAGS) -c $< -o $(OUTPUT_DIRECTORY)/$@

clean:
	rm -rf *.o $(TARGET)
