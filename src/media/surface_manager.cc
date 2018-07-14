#include "surface_manager.h"

namespace media {

  EGLContentVideoSurface* EGLContentVideoSurface::Create() {
  }

  EGLContentVideoSurface::EGLContentVideoSurface() {
  }

  EGLContentVideoSurface::~EGLContentVideoSurface() {
  }

  void* EGLContentVideoSurface::GetNativeSurface() {
  }

  void EGLContentVideoSurface::SetSize(int width, int height,
				       EGLContent::AspectRatio aspect_ratio) {
  }

  gfx::Size EGLContentVideoSurface::CodedSize() {
  }

  gfx::Rect EGLContentVideoSurface::VisibleRect() {
  }

  gfx::Size EGLContentVideoSurface::NaturalSize() {
  }



  EGLContentSurfaceManager() {
  }

  ~EGLContentSurfaceManager() {
  }

  void Initialise(gpu::GpuChannelManager* gpu_channel_manager,
		  VideoDecoderConfig& config,
		  int max_surface_count) {
    if (surfaces_.size() > 0) {
      available_surfaces_.clear();
      reserved_surfaces_.clear();
      surfaces_.clear();
    }

    for (int i = 0; i < max_surface_count; i++) {
      std::unique_ptr<EGLContentVideoSurface> surface(
	EGLContentVideoSurface::Create(config, id));
      surfaces_.push_back(std::move(surface));
      available_surfaces_.push(surface.get());
    }
  }

  EGLContentVideoSurface* GetSurface() {
  }
}
