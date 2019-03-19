// Copyright (c) 2019 Slack Technologies, Inc.
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef ATOM_RENDERER_ELECTRON_API_SERVICE_IMPL_H_
#define ATOM_RENDERER_ELECTRON_API_SERVICE_IMPL_H_

#include <string>

#include "content/public/renderer/render_frame.h"
#include "content/public/renderer/render_frame_observer.h"
#include "electron/atom/common/api/api.mojom.h"
#include "mojo/public/cpp/bindings/associated_binding.h"

namespace atom {

class ElectronApiServiceImpl : public electron_api::mojom::ElectronRenderer,
                               public content::RenderFrameObserver {
 public:
  static void CreateMojoService(
      content::RenderFrame* render_frame,
      electron_api::mojom::ElectronRendererAssociatedRequest request);

  void Message(bool internal,
               const std::string& channel,
               base::Value arguments,
               int32_t sender_id) override;

 private:
  ~ElectronApiServiceImpl() override;
  ElectronApiServiceImpl(
      content::RenderFrame* render_frame,
      electron_api::mojom::ElectronRendererAssociatedRequest request);

  // RenderFrameObserver implementation.
  void OnDestruct() override;

  mojo::AssociatedBinding<electron_api::mojom::ElectronRenderer> binding_;

  content::RenderFrame* render_frame_;
  bool isolated_world_;

  base::WeakPtr<ElectronApiServiceImpl> weak_this_;
  base::WeakPtrFactory<ElectronApiServiceImpl> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(ElectronApiServiceImpl);
};

}  // namespace atom

#endif  // ATOM_RENDERER_ELECTRON_API_SERVICE_IMPL_H_
