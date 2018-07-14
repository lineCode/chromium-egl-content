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

#include "base/bind.h"

#include "content/child/service_factory.h"

#include "content/eglcontent/content/content_gpu_client.h"

namespace content {

  namespace {

    static std::unique_ptr<::shell::Service> CreateEGLContentMediaApplication(
      EGLContent::MediaDelegate* media_delegate,
      gpu::GpuChannelManager* gpu_channel_manager,
      const base::Closure& quit_closure) {
      std::unique_ptr<media::EGLContentMojoMediaClient> mojo_media_client(
	new media::EGLContentMojoMediaClient(media_delegate, gpu_channel_manager));
      return std::unique_ptr<::shell::Service>(
	new ::media::MojoMediaApplication(
	  std::move(mojo_media_client), quit_closure));
    }

  }

  class EGLContentGPUServiceFactory : public ServiceFactory {
    public:
      EGLContentGPUServiceFactory(EGLContent::MediaDelegate* media_delegate)
	: media_delegate_(media_delegate) {}

      ~EGLContentGPUServiceFactory() override {}

      void SetGPUChannelManager(gpu::GpuChannelManager* gpu_channel_manager) {
	gpu_channel_manager_ = gpu_channel_manager;
      }

      void RegisterServices(ServiceMap* services) {
	ServiceInfo info;
	info.factory = base::Bind(
	  &CreateEGLContentMediaApplication,
	  base::Unretained(media_delegate_),
	  base::Unretained(gpu_channel_manager));
	info.use_own_thread = true;
	services->insert(std::make_pair("service:media", info));
      }

    private:

      EGLContent::MediaDelegate* media_delegate_;
      gpu::GpuChannelManager* gpu_channel_manager_;

      DISALLOW_COPY_AND_ASSIGN(EGLContentGPUServiceFactory);
  };

  EGLContentGPUClient::EGLContentGPUClient(EGLContent::MediaDelegate* media_delegate)
    : service_factory_(new EGLContentGPUServiceFactory(media_delegate)) {
  }

  EGLContentGPUClient::~EGLContentGPUClient() {
  }

  void EGLContentGPUClient::Initialize(base::FieldTrialList::Observer* observer) {
  }

  void EGLContentGPUClient::ExposeInterfacesToBrowser(
    shell::InterfaceRegistry* registry,
    const gpu::GpuPreferences& gpu_preferences,
    gpu::GpuChannelManager* gpu_channel_manager) {
    service_factory_->SetGPUChannelManager(gpu_channel_manager);
    registry->AddInterface(
      base::Bind(&EGLContentGPUClient::BindServiceRequest, base::Unretained(this)));
  }

  void EGLContentGPUClient::ConsumeInterfacesFromBrowser(
    shell::InterfaceProvider* provider) {
    // Connect to a service in another process ?
  }

  gpu::SyncPointManager* EGLContentGPUClient::GetSyncPointManager() {
  }

  void EGLContentGPUClient::BindServiceRequest(
    shell::mojom::ServiceFactoryRequest request) {
    service_factory_bindings_.AddBinding(
      service_factory_.get(), std::move(request));
  }

}
