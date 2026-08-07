//  -*-  coding: utf-8-with-signature;  mode: c++  -*-  //
/*************************************************************************
**                                                                      **
**                  ---   Graphics Test Project.   ---                  **
**                                                                      **
**          Copyright (C), 2025-2026, Takahiro Itou                     **
**          All Rights Reserved.                                        **
**                                                                      **
**          License: (See COPYING or LICENSE files)                     **
**          GNU Affero General Public License (AGPL) version 3,         **
**          or (at your option) any later version.                      **
**                                                                      **
*************************************************************************/

/**
**      An Implementation of FullColorImage class.
**
**      @file       Images/FullColorImage.cpp
**/

#include    "Sample/Images/FullColorImage.h"


SAMPLE_NAMESPACE_BEGIN
namespace  Images  {

namespace  {

}   //  End of (Unnamed) namespace.


//========================================================================
//
//    FullColorImage  class.
//

//========================================================================
//
//    Constructor(s) and Destructor.
//

//----------------------------------------------------------------
//    インスタンスを初期化する
//  （デフォルトコンストラクタ）。

FullColorImage::FullColorImage()
    : m_iWidth (0),
      m_iHeight(0),
      m_cbPixel(3),
      m_lStride(0),
      m_lpBits(nullptr),
      m_lpAlloc(nullptr),
      m_lpOrig(nullptr)
{
}

//----------------------------------------------------------------
//    インスタンスを破棄する
//  （デストラクタ）。
//

FullColorImage::~FullColorImage()
{
    freeImageBuffer();
}

//========================================================================
//
//    Public Member Functions (Implement Pure Virtual).
//

//========================================================================
//
//    Public Member Functions (Overrides).
//

//========================================================================
//
//    Public Member Functions (Pure Virtual Functions).
//

//========================================================================
//
//    Public Member Functions (Virtual Functions).
//

//----------------------------------------------------------------
//    イメージを作成する。
//

FullColorImage::LpWriteBuf
FullColorImage::allocateImage(
        const  PosUnitType  nWidth,
        const  PosUnitType  nHeight,
        const  LenUnitType  cbPixel,
        const  LenUnitType  lStride)
{
    LpWritePixelBuf ptrBuf  = nullptr;
    LenUnitType     cbSize  = 0;
    LenUnitType     wStride = lStride;

    freeImageBuffer();


    if ( wStride == 0 ) {
        wStride = computeBytesPerPixel(nWidth, cbPixel);
    }
    cbSize  = (wStride >= 0 ? wStride : -wStride) * nHeight;
    ptrBuf  = new BtByte [cbSize];

    this->createImage(nWidth, nHeight, cbSize, wStride, ptrBuf);
    return ( this->m_lpAlloc = ptrBuf );
}

//----------------------------------------------------------------
//    イメージを作成する。
//

void
FullColorImage::createImage(
        const  PosUnitType  nWidth,
        const  PosUnitType  nHeight,
        const  LenUnitType  cbPixel,
        const  LenUnitType  lStride,
        LpWriteBuf   const  lpBits)
{
    //  バッファのアドレスと原点に対応するアドレスを保存。  //
    this->m_lpBits  = static_cast<BtByte *>(lpBits);
    if ( lStride < 0 ) {
        //  ボトムアップ形式
        this->m_lpOrig  = this->m_lpBits - ((nHeight - 1) * lStride);
    } else {
        //  トップダウン形式
        this->m_lpOrig  = this->m_lpBits;
    }

    this->m_iWidth  = nWidth;
    this->m_iHeight = nHeight;
    this->m_cbPixel = cbPixel;
    this->m_lStride = lStride;
}

//----------------------------------------------------------------
//    サンプル画像を描画する。
//

void
FullColorImage::drawSample(
        const  ColorArgb32  colBG,
        const  ColorArgb32  colTL,
        const  ColorArgb32  colTR,
        const  ColorArgb32  colBL,
        const  ColorArgb32  colBR)
{
    const  PosUnitType  iW  = this->m_iWidth;
    const  PosUnitType  iH  = this->m_iHeight;

    fillRectangle(0, 0, iW, iH, colBG);

    const  PosUnitType  rW  = iW / 4;
    const  PosUnitType  rH  = iH / 4;

    fillTriangle(rW * 1, rH * 1, rW * 1 + rW, rH * 1 + rH, colTL);
    fillTriangle(rW * 2, rH * 1, rW * 2 + rW, rH * 1 + rH, colTR);
    fillTriangle(rW * 1, rH * 2, rW * 1 + rW, rH * 2 + rH, colBL);
    fillTriangle(rW * 2, rH * 2, rW * 2 + rW, rH * 2 + rH, colBR);
}

//----------------------------------------------------------------
//    確保したバッファを解放する。
//

void
FullColorImage::freeImageBuffer()
{
    LpWritePixelBuf ptr = this->m_lpAlloc;
    if ( ptr == nullptr ) {
        return;
    }

    delete  [] ptr;

    this->m_lpBits  = nullptr;
    this->m_lpOrig  = nullptr;
    this->m_lpAlloc = nullptr;
}


//========================================================================
//
//    Public Member Functions.
//

//----------------------------------------------------------------
//    矩形を描画する。
//

void
FullColorImage::fillRectangle(
        const  PosUnitType  x1,
        const  PosUnitType  y1,
        const  PosUnitType  x2,
        const  PosUnitType  y2,
        const  ColorArgb32  color)
{
    const   BtByte  cB  = ( color        & 0xFF);
    const   BtByte  cG  = ((color >>  8) & 0xFF);
    const   BtByte  cR  = ((color >> 16) & 0xFF);
    const   BtByte  cA  = ((color >> 24) & 0xFF);
    const   LenUnitType     cbRems  = this->m_cbPixel - 3;

    for ( PosUnitType y = y1; y < y2; ++ y ) {
        LpWritePixelBuf ptr = getPixel(x1, y);
        for ( PosUnitType x = x1; x < x2; ++ x ) {
            *(ptr ++) = cB;
            *(ptr ++) = cG;
            *(ptr ++) = cR;
            if ( cbRems == 1 ) {
                *(ptr ++) = cA;
            } else {
                ptr += cbRems;
            }
        }
    }

    return;
}

//----------------------------------------------------------------
//    三角形を描画する。
//

void
FullColorImage::fillTriangle(
        const  PosUnitType  x1,
        const  PosUnitType  y1,
        const  PosUnitType  x2,
        const  PosUnitType  y2,
        const  ColorArgb32  color)
{
    const   BtByte  cB  = ( color        & 0xFF);
    const   BtByte  cG  = ((color >>  8) & 0xFF);
    const   BtByte  cR  = ((color >> 16) & 0xFF);
    const   BtByte  cA  = ((color >> 24) & 0xFF);
    const   LenUnitType     cbRems  = this->m_cbPixel - 3;

    PosUnitType tmp = 1;
    for ( PosUnitType y = y1; y < y2; ++ y ) {
        LpWritePixelBuf ptr = getPixel(x1, y);
        PosUnitType  lastX  = (x1 + tmp);
        if ( x2 < lastX ) { lastX = x2; }
        for ( PosUnitType x = x1; x < lastX; ++ x ) {
            *(ptr ++) = cB;
            *(ptr ++) = cG;
            *(ptr ++) = cR;
            if ( cbRems == 1 ) {
                *(ptr ++) = cA;
            } else {
                ptr += cbRems;
            }
        }
        ++ tmp;
    }

    return;
}

//========================================================================
//
//    Accessors.
//

//========================================================================
//
//    Protected Member Functions.
//

//========================================================================
//
//    For Internal Use Only.
//

}   //  End of namespace  Images
SAMPLE_NAMESPACE_END
