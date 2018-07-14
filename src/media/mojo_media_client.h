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

#ifndef EGLCONTENT_MEDIA_MOJO_MEDIA_CLIENT_H_
# define EGLCONTENT_MEDIA_MOJO_MEDIA_CLIENT_H_

#include <memory>

#include "base/macros.h"
#include "base/memory/ref_counted.h"
#include "media/audio/audio_manager.h"
#include "media/mojo/services/mojo_media_client.h"

namespace EGLContent {
  class MediaDelegate;
}

namespace media {

  class EGLContentMojoMediaClient : public MojoMediaClient {

    public:
      EGLContentMojoMediaClient(
	EGLContent::MediaDelegate* delegate,
	gpu::GpuChannelManager* gpu_channel_manager);
      ~EGLContentMojoMediaClient() override;

      void Initialize() override;

      std::unique_ptr<AudioDecoder> CreateAudioDecoder(
	scoped_refptr<base::SingleThreadTaskRunner> task_runner) override;

      std::unique_ptr<VideoDecoder> CreateVideoDecoder(
	scoped_refptr<base::SingleThreadTaskRunner> task_runner) override;

      // Returns the output sink used for rendering audio on |audio_device_id|.
      // May be null if the RendererFactory doesn't need an audio sink.
      scoped_refptr<AudioRendererSink> CreateAudioRendererSink(
	const std::string& audio_device_id) override;

      // Returns the output sink used for rendering video.
      // May be null if the RendererFactory doesn't need a video sink.
      std::unique_ptr<VideoRendererSink> CreateVideoRendererSink(
	const scoped_refptr<base::SingleThreadTaskRunner>& task_runner) override;

      // Returns the RendererFactory to be used by MojoRendererService.
      std::unique_ptr<RendererFactory> CreateRendererFactory(
	const scoped_refptr<MediaLog>& media_log) override;

      // Returns the CdmFactory to be used by MojoCdmService.
      std::unique_ptr<CdmFactory> CreateCdmFactory(
	shell::mojom::InterfaceProvider* interface_provider) override;

    private:

      EGLContent::MediaDelegate* delegate_;
      gpu::GpuChannelManager* gpu_channel_manager_;

      DISALLOW_COPY_AND_ASSIGN(EGLContentMojoMediaClient);
  };

}

#endif /* !EGLCONTENT_MEDIA_MOJO_MEDIA_CLIENT.H */
