#ifndef EGLCONTENT_MEDIA_SURFACE_MANAGER_H_
# define EGLCONTENT_MEDIA_SURFACE_MANAGER_H_

#include "ui/gfx/geometry/size.h"
#include "ui/gfx/geometry/size.h"

namespace media {

  class EGLContentVideoSurface : public EGLContent::VideoSurface {

    public:

      static EGLContentVideoSurface* Create(uint32_t id);

      ~EGLContentVideoSurface();

      void* GetNativeSurface();
      gfx::Size CodedSize();
      gfx::Rect VisibleRect();
      gfx::Size NaturalSize();

      int Id();

    private:
      EGLContentVideoSurface();

  };

  class EGLContentSurfaceManager {

    public:

      EGLContentSurfaceManager(gpu::GpuChannelManager* gpu_channel_manager);
      ~EGLContentSurfaceManager();

      void Initialise();
      EGLContentVideoSurface* GetSurface();
      void ReturnSurface(uint32_t id);

    private:

      gpu::GpuChannelManager* gpu_channel_manager;

      std::queue<EGLContentVideoSurface*> available_surfaces_;
      std::map<uint32_t, EGLContentVideoSurface*> reserved_surfaces_;
      std::vector<std::unique_ptr<EGLContentVideoSurface> > surfaces_;

  };

}

#endif /* !EGLCONTENT_MEDIA_SURFACE_MANAGER.H */
