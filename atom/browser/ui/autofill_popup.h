// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ATOM_BROWSER_UI_AUTOFILL_POPUP_H_
#define ATOM_BROWSER_UI_AUTOFILL_POPUP_H_

#include <vector>

#include "atom/browser/ui/views/autofill_popup_view.h"
#include "content/public/browser/render_frame_host.h"
#include "ui/gfx/font_list.h"
#include "ui/native_theme/native_theme.h"
#include "ui/views/view.h"
#include "ui/views/widget/widget.h"

namespace atom {

class AutofillPopupView;

class AutofillPopup : public views::ViewObserver {
 public:
  AutofillPopup();
  ~AutofillPopup();

  void CreateView(content::RenderFrameHost* render_frame,
                  bool offscreen,
                  views::View* parent,
                  const gfx::RectF& bounds);
  void Hide();

  void SetItems(const std::vector<base::string16>& values,
                const std::vector<base::string16>& labels);
  void UpdatePopupBounds();

 private:
  friend class AutofillPopupView;

  // views::ViewObserver:
  void OnViewBoundsChanged(views::View* view) override;
  void OnViewIsDeleting(views::View* view) override;

  void AcceptSuggestion(int index);

  int GetDesiredPopupHeight();
  int GetDesiredPopupWidth();
  gfx::Rect GetRowBounds(int i);
  const gfx::FontList& GetValueFontListForRow(int index) const;
  const gfx::FontList& GetLabelFontListForRow(int index) const;
  ui::NativeTheme::ColorId GetBackgroundColorIDForRow(int index) const;

  int GetLineCount();
  base::string16 GetValueAt(int i);
  base::string16 GetLabelAt(int i);
  int LineFromY(int y) const;

  int selected_index_;

  // Popup location
  gfx::Rect popup_bounds_;
  gfx::Rect popup_bounds_in_view_;

  // Bounds of the autofilled element
  gfx::Rect element_bounds_;

  // Datalist suggestions
  std::vector<base::string16> values_;
  std::vector<base::string16> labels_;

  // Font lists for the suggestions
  gfx::FontList smaller_font_list_;
  gfx::FontList bold_font_list_;

  // For sending the accepted suggestion to the render frame that
  // asked to open the popup
  content::RenderFrameHost* frame_host_ = nullptr;

  // The popup view. The lifetime is managed by the owning Widget
  AutofillPopupView* view_ = nullptr;

  // The parent view that the popup view shows on. Weak ref.
  views::View* parent_ = nullptr;

  DISALLOW_COPY_AND_ASSIGN(AutofillPopup);
};

}  // namespace atom

#endif  // ATOM_BROWSER_UI_AUTOFILL_POPUP_H_
