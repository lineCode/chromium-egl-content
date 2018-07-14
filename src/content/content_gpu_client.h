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

#ifndef EGLCONTENT_CONTENT_CONTENT_GPU_CLIENT_H_
# define EGLCONTENT_CONTENT_CONTENT_GPU_CLIENT_H_

#include "base/macros.h"

#include "mojo/public/cpp/bindings/binding_set.h"

#include "services/shell/public/interfaces/service_factory.mojom.h"

#include "content/public/gpu/content_gpu_client.h"

namespace EGLContent {
  class MediaDelegate;
}

namespace content {

  class EGLContentGPUServiceFactory;

  class EGLContentGPUClient : public ContentGpuClient {
    public:
      EGLContentGPUClient(EGLContent::MediaDelegate* media_delegate);
      ~EGLContentGPUClient();

      // Initializes the client. This sets up the field trial synchronization
      // mechanism, which will notify |observer| when a field trial is activated,
      // which should be used to inform the browser process of this state.
      void Initialize(base::FieldTrialList::Observer* observer) override;

      // Allows the client to expose interfaces from the GPU process to the browser
      // process via |registry|.
      void ExposeInterfacesToBrowser(
	shell::InterfaceRegistry* registry,
	const gpu::GpuPreferences& gpu_preferences,
	gpu::GpuChannelManager* gpu_channel_manager) override;

      // Allow the client to bind interfaces exposed by the browser process.
      void ConsumeInterfacesFromBrowser(
	shell::InterfaceProvider* provider) override;

      // Allows client to supply a SyncPointManager instance instead of having
      // content internally create one.
      gpu::SyncPointManager* GetSyncPointManager() override;

    private:

      void BindServiceRequest(
	shell::mojom::ServiceFactoryRequest request);

      std::unique_ptr<EGLContentGPUServiceFactory> service_factory_;
      mojo::BindingSet<shell::mojom::ServiceFactory> service_factory_bindings_;

      DISALLOW_COPY_AND_ASSIGN(EGLContentGPUClient);
  };

}

#endif /* !EGLCONTENT_CONTENT_CONTENT_GPU_CLIENT.H */
