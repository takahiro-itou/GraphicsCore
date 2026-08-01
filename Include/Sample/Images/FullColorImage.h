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
**      An Interface of FullColorImage class.
**
**      @file       Images/FullColorImage.h
**/

#if !defined( SAMPLE_IMAGES_INCLUDED_FULL_COLOR_IMAGE_H )
#    define   SAMPLE_IMAGES_INCLUDED_FULL_COLOR_IMAGE_H

#include    "Sample/Common/SampleSettings.h"


SAMPLE_NAMESPACE_BEGIN
namespace  Images  {

//========================================================================
//
//    FullColorImage  class.
//

class  FullColorImage
{

//========================================================================
//
//    Internal Type Definitions.
//
public:

    typedef     int             PosUnitType;

    typedef     int             LenUnitType;

    typedef     long            OffsetType;

    typedef     int             ColorArgb32;

    typedef     void  *         LpWriteBuf;

    typedef     unsigned char   BtByte;

    typedef     BtByte *        LpWritePixelBuf;

    typedef     const BtByte *  LpcReadPixelBuf;


//========================================================================
//
//    Constructor(s) and Destructor.
//
public:

    //----------------------------------------------------------------
    /**   インスタンスを初期化する
    **  （デフォルトコンストラクタ）。
    **
    **/
    FullColorImage();

    //----------------------------------------------------------------
    /**   インスタンスを破棄する
    **  （デストラクタ）。
    **
    **/
    virtual  ~FullColorImage();

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
public:

    //----------------------------------------------------------------
    /**   イメージを作成する。
    **
    **  @param [in] nWidth    イメージの幅
    **  @param [in] nHeight   イメージの高さ
    **  @param [in] cbPixel   ピクセル当たりのバイト数。
    **  @param [in] lStride   行当たりのバイト数。
    **  @param [in] lpBits    イメージデータ。
    **/
    virtual  void
    createImage(
            const  PosUnitType  nWidth,
            const  PosUnitType  nHeight,
            const  LenUnitType  cbPixel,
            const  LenUnitType  lStride,
            LpWriteBuf   const  lpBits);

    //----------------------------------------------------------------
    /**   サンプル画像を描画する。
    **
    **/
    virtual  void
    drawSample();

//========================================================================
//
//    Public Member Functions.
//
public:

    //----------------------------------------------------------------
    /**   矩形を描画する。
    **
    **/
    void
    fillRectangle(
            const  PosUnitType  x1,
            const  PosUnitType  y1,
            const  PosUnitType  x2,
            const  PosUnitType  y2,
            const  ColorArgb32  color);

//========================================================================
//
//    Accessors.
//
public:

    inline  const   OffsetType
    getOffset(
            const  PosUnitType  x,
            const  PosUnitType  y)  const
    {
        // return ( (this->m_iHeight - y - 1) * (this->m_lStride)
        //          + ((this->m_cbPixel) * x)
        // );
        return ( (y) * (this->m_lStride) + ((this->m_cbPixel) * x) );
    }

    inline  LpcReadPixelBuf
    getImage()  const
    {
        return ( this->m_lpBits );
    }

    inline  LpWritePixelBuf
    getImage()
    {
        return ( this->m_lpBits );
    }

    inline  LpcReadPixelBuf
    getOrigin()  const
    {
        return ( this->m_lpOrig );
    }

    inline  LpWritePixelBuf
    getOrigin()
    {
        return ( this->m_lpOrig );
    }

    inline  LpcReadPixelBuf
    getPixel(
            const  PosUnitType  x,
            const  PosUnitType  y)  const
    {
        return ( this->m_lpOrig + getOffset(x, y) );
    }

    inline  LpWritePixelBuf
    getPixel(
            const  PosUnitType  x,
            const  PosUnitType  y)
    {
        return ( this->m_lpOrig + getOffset(x, y) );
    }

//========================================================================
//
//    Protected Member Functions.
//

//========================================================================
//
//    For Internal Use Only.
//

//========================================================================
//
//    Member Variables.
//
private:

    PosUnitType         m_iWidth;
    PosUnitType         m_iHeight;
    LenUnitType         m_cbPixel;
    LenUnitType         m_lStride;

    LpWritePixelBuf     m_lpBits;

    /**   原点に対応するアドレス。  **/
    LpWritePixelBuf     m_lpOrig;

//========================================================================
//
//    Other Features.
//
private:
    typedef     FullColorImage      This;
    FullColorImage      (const  This  &);
    This &  operator =  (const  This  &);
public:
    //  テストクラス。  //
    friend  class   FullColorImageTest;
};

}   //  End of namespace  Images
SAMPLE_NAMESPACE_END

#endif
