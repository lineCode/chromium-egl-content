#ifndef MEDIA_DELEGATE_H_
# define MEDIA_DELEGATE_H_

namespace EGLContent {

  class MediaDelegate {

    public:

      virtual void InitialiseMediaPlatform() = 0;
      virtual AudioDecoderDelegate* CreateAudioDecoderDelegate() = 0;
      virtual VideoDecoderDelegate* CreateVideoDecoderDelegate() = 0;
      virtual AudioSinkDelegate* CreateAudioSinkDelegate() = 0;
      virtual VideoSinkDelegate* CreateVideoSinkDelegate() = 0;
  };

}

#endif /* !MEDIA_DELEGATE.H */
