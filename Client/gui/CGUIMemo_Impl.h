/*****************************************************************************
 *
 *  PROJECT:     Multi Theft Auto v1.0
 *  LICENSE:     See LICENSE in the top level directory
 *  FILE:        gui/CGUIMemo_Impl.h
 *  PURPOSE:     Multi-line edit box widget class
 *
 *  Multi Theft Auto is available from http://www.multitheftauto.com/
 *
 *****************************************************************************/

#ifndef __CGUIMEMO_IMPL_H
#define __CGUIMEMO_IMPL_H

#include <gui/CGUIMemo.h>
#include "CGUIElement_Impl.h"

class CGUIMemo_Impl : public CGUIMemo, public CGUIElement_Impl, public CGUITabListItem
{
public:
    CGUIMemo_Impl(class CGUI_Impl* pGUI, CGUIElement* pParent = NULL, const char* szText = "");
    ~CGUIMemo_Impl(void);

    void SetReadOnly(bool bReadOnly);
    bool IsReadOnly(void);

    size_t GetCaretIndex(void);
    void   SetCaretIndex(size_t Index);

    float GetVerticalScrollPosition(void);
    void  SetVerticalScrollPosition(float fPosition);
    float GetMaxVerticalScrollPosition(void);
    float GetScrollbarDocumentSize(void);
    float GetScrollbarPageSize(void);

    void         SetSelection(unsigned int uiStart, unsigned int uiEnd);
    unsigned int GetSelectionStart(void);
    unsigned int GetSelectionEnd(void);
    unsigned int GetSelectionLength(void);

    void EnsureCaratIsVisible(void);

    bool ActivateOnTab(void);

    void SetTextChangedHandler(const GUI_CALLBACK& Callback);

    eCGUIType GetType(void) { return CGUI_MEMO; };

    #include "CGUIElement_Inc.h"

private:
    bool Event_TextChanged(const CEGUI::EventArgs& e);
    bool Event_OnKeyDown(const CEGUI::EventArgs& e);

    GUI_CALLBACK m_TextChanged;
};

#endif
