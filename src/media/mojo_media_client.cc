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

#include "base/message_loop/message_loop.h"

#include "content/eglcontent/media/mojo_media_client.h"
#include "content/eglcontent/media/audio_decoder.h"
#include "content/eglcontent/media/video_decoder.h"
#include "content/eglcontent/media/audio_renderer_sink.h"
#include "content/eglcontent/media/video_renderer_sink.h"
#include "content/eglcontent/media/renderer_factory.h"
#include "content/eglcontent/media/cdm_factory.h"

namespace media {

  EGLContentMojoMediaClient::EGLContentMojoMediaClient(
    EGLContent::MediaDelegate* delegate,
    gpu::GpuChannelManager* gpu_channel_manager)
    : delegate_(delegate),
      gpu_channel_manager_() {
  }

  EGLContentMojoMediaClient::~EGLContentMojoMediaClient() {
    if (delegate_)
      delegate_->Cleanup();
  }

  void EGLContentMojoMediaClient::Initialize() {
    if (delegate_)
      delegate_->InitialiseMediaPlatform();
  }

  std::unique_ptr<AudioDecoder> EGLContentMojoMediaClient::CreateAudioDecoder(
    scoped_refptr<base::SingleThreadTaskRunner> task_runner) {
    return base::MakeUnique<EGLContentAudioDecoder>(
      delegate_->CreateAudioDecoderDelegate(), task_runner);
  }

  std::unique_ptr<VideoDecoder> EGLContentMojoMediaClient::CreateVideoDecoder(
    scoped_refptr<base::SingleThreadTaskRunner> task_runner,
    mojom::CommandBufferIdPtr command_buffer_id) {
    command_buffer_id->channel_token;
    command_buffer_id->route_id;
    return base::MakeUnique<EGLContentVideoDecoder>(
      delegate_->CreateVideoDecoderDelegate(), task_runner, stub);
  }

  scoped_refptr<AudioRendererSink> EGLContentMojoMediaClient::CreateAudioRendererSink(
    const std::string& audio_device_id) {
    EGLContent::AudioSinkDelegate* sink_delegate =
      delegate_->CreateAudioSinkDelegate();

    if (sink_delegate)
      return new EGLContentAudioRendererSink(sink_delegate);

    return new NullAudioSink(base::MessageLoop::Current()->task_runner());
  }

  std::unique_ptr<VideoRendererSink> EGLContentMojoMediaClient::CreateVideoRendererSink(
    const scoped_refptr<base::SingleThreadTaskRunner>& task_runner) {
    EGLContent::VideoSinkDelegate* sink_delegate =
      delegate_->CreateVideoSinkDelegate();

    if (sink_delegate)
      return new EGLContentVideoRendererSink(sink_delegate);

    return base::MakeUnique<NullVideoSink>(
      false, base::TimeDelta::FromSecondsD(1.0 / 60),
      NullVideoSink::NewFrameCB(), task_runner);
  }

  std::unique_ptr<RendererFactory> EGLContentMojoMediaClient::CreateRendererFactory(
    const scoped_refptr<MediaLog>& media_log) {
    return base::MakeUnique<EGLContentRendererFactory>(
      delegate_, media_log);
  }

  std::unique_ptr<CdmFactory> EGLContentMojoMediaClient::CreateCdmFactory(
    shell::mojom::InterfaceProvider* interface_provider) {
    return base::MakeUnique<EGLContentCDMFactory>(
      delegate_, interface_provider);
  }

}
