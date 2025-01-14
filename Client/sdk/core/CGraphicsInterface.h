/*****************************************************************************
 *
 *  PROJECT:     Multi Theft Auto v1.0
 *  LICENSE:     See LICENSE in the top level directory
 *  FILE:        sdk/core/CGraphicsInterface.h
 *  PURPOSE:     Graphics subsystem interface
 *
 *  Multi Theft Auto is available from http://www.multitheftauto.com/
 *
 *****************************************************************************/

#ifndef __CGRAPHICSINTERFACE_H
#define __CGRAPHICSINTERFACE_H

#include "CVector.h"

struct ID3DXFont;
struct IDirect3DDevice9;
struct IDirect3DTexture9;

enum eFontType
{
    FONT_DEFAULT = 0,
    FONT_DEFAULT_BOLD,
    FONT_CLEAR,
    FONT_ARIAL,
    FONT_SANS,
    FONT_PRICEDOWN,
    FONT_BANKGOTHIC,
    FONT_DIPLOMA,
    FONT_BECKETT,
    FONT_UNIFONT,
    NUM_FONTS
};

enum eFontQuality
{
    FONT_QUALITY_DEFAULT = DEFAULT_QUALITY,
    FONT_QUALITY_DRAFT = DRAFT_QUALITY,
    FONT_QUALITY_PROOF = PROOF_QUALITY,

#if( WINVER >= 0x0400 )
    FONT_QUALITY_NONANTIALIASED = NONANTIALIASED_QUALITY,
    FONT_QUALITY_ANTIALIASED = ANTIALIASED_QUALITY,
#endif

#if( _WIN32_WINNT >= _WIN32_WINNT_WINXP )
    FONT_QUALITY_CLEARTYPE = CLEARTYPE_QUALITY,
    FONT_QUALITY_CLEARTYPE_NATURAL = CLEARTYPE_NATURAL_QUALITY,
#endif

    NUM_QUALITIES
};

namespace EBlendMode
{
    enum EBlendModeType
    {
        NONE,
        BLEND,                   // Alpha blend
        ADD,                     // Color add                          (used for making composite textures with a premultiplied source)
        MODULATE_ADD,            // Modulate color with alpha then add (used for making composite textures with a non-premultiplied source)
        OVERWRITE,               // Blat everything
    };
}
using EBlendMode::EBlendModeType;

class CGraphicsInterface
{
public:
    virtual IDirect3DDevice9* GetDevice(void) = 0;

    virtual void CalcWorldCoors(CVector* vecScreen, CVector* vecWorld) = 0;
    virtual void CalcScreenCoors(CVector* vecWorld, CVector* vecScreen) = 0;

    virtual void DrawString(int iLeft, int iTop, int iRight, int iBottom, unsigned long dwColor, const char* wszText, float fScaleX, float fScaleY,
                            unsigned long ulFormat, ID3DXFont* pDXFont = NULL, bool bOutline = false) = 0;
    virtual void DrawString(int iX, int iY, unsigned long dwColor, float fScale, const char* szText, ...) = 0;

    virtual void DrawLine3D(const CVector& vecBegin, const CVector& vecEnd, unsigned long ulColor, float fWidth = 1.0f) = 0;
    virtual void DrawRectangle(float fX, float fY, float fWidth, float fHeight, unsigned long ulColor, bool bSubPixelPositioning = false) = 0;

    virtual void           SetBlendMode(EBlendModeType blendMode) = 0;
    virtual EBlendModeType GetBlendMode(void) = 0;

    virtual unsigned int GetViewportWidth(void) = 0;
    virtual unsigned int GetViewportHeight(void) = 0;

    virtual void  SetAspectRatioAdjustmentEnabled(bool bEnabled, float fSourceRatio = 4 / 3.f) = 0;
    virtual bool  IsAspectRatioAdjustmentEnabled(void) = 0;
    virtual float GetAspectRatioAdjustmentSourceRatio(void) = 0;
    virtual void  SetAspectRatioAdjustmentSuspended(bool bSuspended) = 0;
    virtual float ConvertPositionForAspectRatio(float fY) = 0;
    virtual void  ConvertSideForAspectRatio(float* pfY, float* pfHeight) = 0;

    virtual float GetDXFontHeight(float fScale = 1.0f, ID3DXFont* pDXFont = NULL) = 0;
    virtual float GetDXCharacterWidth(char c, float fScale = 1.0f, ID3DXFont* pDXFont = NULL) = 0;
    virtual float GetDXTextExtent(const char* szText, float fScale = 1.0f, ID3DXFont* pDXFont = NULL, bool bColorCoded = false) = 0;

    virtual bool LoadAdditionalDXFont(std::string strFontPath, std::string strFontName, unsigned int uiHeight, bool bBold, ID3DXFont** ppD3DXFont) = 0;
    virtual bool LoadAdditionalDXFont(std::string strFontPath, std::string strFontName, unsigned int uiHeight, bool bBold, DWORD ulQuality,
                                      ID3DXFont** ppD3DXFont) = 0;
    virtual bool DestroyAdditionalDXFont(std::string strFontPath, ID3DXFont* pD3DXFont) = 0;

    virtual ID3DXFont* GetFont(eFontType fontType = FONT_DEFAULT, float* pfOutScaleUsed = NULL, float fRequestedScale = 1,
                               const char* szCustomScaleUser = NULL) = 0;

    virtual void DrawTexture(CTextureItem* texture, float fX, float fY, float fScaleX = 1.0f, float fScaleY = 1.0f, float fRotation = 0.0f,
                             float fCenterX = 0.0f, float fCenterY = 0.0f, DWORD dwColor = 0xFFFFFFFF, float fU = 0, float fV = 0, float fSizeU = 1,
                             float fSizeV = 1, bool bRelativeUV = true) = 0;

    // Queued up drawing
    virtual void DrawLineQueued(float fX1, float fY1, float fX2, float fY2, float fWidth, unsigned long ulColor, bool bPostGUI) = 0;

    virtual void DrawLine3DQueued(const CVector& vecBegin, const CVector& vecEnd, float fWidth, unsigned long ulColor, bool bPostGUI) = 0;

    virtual void DrawMaterialLine3DQueued(const CVector& vecBegin, const CVector& vecEnd, float fWidth, unsigned long ulColor, CMaterialItem* pMaterial,
                                          float fU = 0, float fV = 0, float fSizeU = 1, float fSizeV = 1, bool bRelativeUV = true, bool bUseFaceToward = false,
                                          const CVector& vecFaceToward = CVector(), bool bPostGUI = false) = 0;

    virtual void DrawRectQueued(float fX, float fY, float fWidth, float fHeight, unsigned long ulColor, bool bPostGUI, bool bSubPixelPositioning = false) = 0;

    virtual void DrawTextureQueued(float fX, float fY, float fWidth, float fHeight, float fU, float fV, float fSizeU, float fSizeV, bool bRelativeUV,
                                   CMaterialItem* pMaterial, float fRotation, float fRotCenOffX, float fRotCenOffY, unsigned long ulColor, bool bPostGUI) = 0;

    virtual void DrawStringQueued(float fLeft, float fTop, float fRight, float fBottom, unsigned long dwColor, const char* wszText, float fScaleX,
                                  float fScaleY, unsigned long ulFormat, ID3DXFont* pDXFont, bool bPostGUI, bool bColorCoded = false,
                                  bool bSubPixelPositioning = false, float fRotation = 0, float fRotationCenterX = 0, float fRotationCenterY = 0) = 0;

    virtual void DrawCircleQueued(float fX, float fY, float fRadius, float fStartAngle, float fStopAngle, unsigned long ulColor, unsigned long ulColorCenter, ushort fSegments, float fRatio, bool bPostGUI) = 0;

    // Subsystems
    virtual CRenderItemManagerInterface* GetRenderItemManager(void) = 0;
    virtual CScreenGrabberInterface*     GetScreenGrabber(void) = 0;
    virtual CPixelsManagerInterface*     GetPixelsManager(void) = 0;

    // Transition between GTA and MTA controlled rendering
    virtual void EnteringMTARenderZone(void) = 0;
    virtual void LeavingMTARenderZone(void) = 0;
    virtual void MaybeEnteringMTARenderZone(void) = 0;
    virtual void MaybeLeavingMTARenderZone(void) = 0;

    // Texture data manipulation
    virtual bool ResizeTextureData(const void* pData, uint uiDataPitch, uint uiWidth, uint uiHeight, uint d3dFormat, uint uiNewWidth, uint uiNewHeight,
                                   CBuffer& outBuffer) = 0;
};

#endif
