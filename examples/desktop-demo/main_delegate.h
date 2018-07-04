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

#ifndef MAIN_DELEGATE_H_
# define MAIN_DELEGATE_H_

#include <string>

#include <eglcontent/main_delegate.h>

class DemoMainDelegate : public EGLContent::MainDelegate {

  public:
    DemoMainDelegate();
    ~DemoMainDelegate();

    void OnStartupComplete() override;
    void BeforeSandboxing() override;
    void AfterSandboxing() override;

};

#endif /* !MAIN_DELEGATE.H */
