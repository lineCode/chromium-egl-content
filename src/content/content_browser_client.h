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

#ifndef EGLCONTENT_CONTENT_CONTENT_BROWSER_CLIENT_H_
# define EGLCONTENT_CONTENT_CONTENT_BROWSER_CLIENT_H_

#include "content/public/browser/content_browser_client.h"

#include "content/eglcontent/browser/browser_main_parts.h"

#include "content/eglcontent/api/main_delegate.h"

#include <memory>

namespace EGLContent {
  struct BrowserConfig;
  class BrowserDelegate;
}

namespace content {

  class EGLContentBrowserClient : public ContentBrowserClient {
    public:

      EGLContentBrowserClient(EGLContent::BrowserConfig& config,
			      EGLContent::BrowserDelegate* delegate);
      ~EGLContentBrowserClient() override;

      /* AUBIN : Many great stuff here to explore in the future !! */

      // Allows the embedder to set any number of custom BrowserMainParts
      // implementations for the browser startup code. See comments in
      // browser_main_parts.h.
      BrowserMainParts* CreateBrowserMainParts(
        const MainFunctionParams& parameters) override;

      // Returns the locale used by the application.
      // This is called on the UI and IO threads.
      std::string GetApplicationLocale() override;

      // Returns the languages used in the Accept-Languages HTTP header.
      // (Not called GetAcceptLanguages so it doesn't clash with win32).
      std::string GetAcceptLangs(BrowserContext* context) override;

      // Returns the default download directory.
      // This can be called on any thread.
      base::FilePath GetDefaultDownloadDirectory();

      // Returns the default filename used in downloads when we have no idea what
      // else we should do with the file.
      std::string GetDefaultDownloadName();

    private:

      EGLContent::BrowserConfig browser_config_;
      EGLContent::BrowserDelegate* delegate_;

      std::unique_ptr<EGLContentBrowserMainParts> browser_main_parts_;

  };

}

#endif // EGLCONTENT_CONTENT_CONTENT_BROWSER_CLIENT_H_
