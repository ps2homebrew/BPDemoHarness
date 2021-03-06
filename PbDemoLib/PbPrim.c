/*
 * PbPrim.c - Primitive functions for Pb demo library
 *
 * Copyright (c) 2004   emoon <daniel@collin.com>
 *
 * Licensed under the AFL v2.0. See the file LICENSE included with this
 * distribution for licensing terms.
 */

#include <tamtypes.h>
#include <kernel.h>
#include "PbPrim.h"
#include "PbGs.h"
#include "PbSpr.h"
#include "PbScreen.h"
#include "PbDma.h"

///////////////////////////////////////////////////////////////////////////////
// Primitive settings
///////////////////////////////////////////////////////////////////////////////

static int g_PbPrimAlphaEnable = FALSE;
static int g_PbPrimContext     = 0;
static u64 g_PbPrimAlpha       = 0;

///////////////////////////////////////////////////////////////////////////////
// void PbPrimSprite
///////////////////////////////////////////////////////////////////////////////

void PbPrimSprite( int x1, int y1, int x2, int y2, int z, int color )
{
  u64* p_store;
  u64* p_data;
  int size = 5;

  x1 += 2048 << 4;
  y1 += 2048 << 4;
  x2 += 2048 << 4;
  y2 += 2048 << 4;

  p_store = p_data = PbSprAlloc( 6*16 );

  //////////////////////////////////////////////////////////////////////////////
  // Check if alpha is enabled

  if( g_PbPrimAlphaEnable == TRUE )
    size++;  
  
  /////////////////////////////////////////////////////////////////////////////
  // Setup for drawing

  *p_data++ = GIF_TAG( size-1, 1, 0, 0, 0, 1 );
  *p_data++ = GIF_AD;

  if( g_PbPrimAlphaEnable == TRUE )
  {
    *p_data++ = g_PbPrimAlpha;
    *p_data++ = GS_ALPHA_1+g_PbPrimContext;
  }

  *p_data++ = GS_SETREG_PRIM( GS_PRIM_PRIM_SPRITE, 0, 0, 0, g_PbPrimAlphaEnable,
                              0, 0, g_PbPrimContext, 0) ;
  *p_data++ = GS_PRIM;

  *p_data++ = color;
  *p_data++ = GS_RGBAQ;

  *p_data++ = GS_SETREG_XYZ2( x1, y1, z );
  *p_data++ = GS_XYZ2;

  *p_data++ = GS_SETREG_XYZ2( x2, y2, z );
  *p_data++ = GS_XYZ2;
  
  PbDmaSend02Spr( p_store, size );
}

///////////////////////////////////////////////////////////////////////////////
// void PbPrimSpriteTexture
///////////////////////////////////////////////////////////////////////////////

void PbPrimSpriteTexture( PbTexture* pTex, int x1, int y1, int u1, int v1, 
                          int x2, int y2, int u2, int v2, int z, int color  )
{
  u64* p_store;
  u64* p_data;
  int  size = 8;

  x1 += 2048 << 4;
  y1 += 2048 << 4;
  x2 += 2048 << 4;
  y2 += 2048 << 4;

  p_store = p_data = PbSprAlloc( 9*16 );

  //////////////////////////////////////////////////////////////////////////////
  // Check if alpha is enabled

  if( g_PbPrimAlphaEnable == TRUE )
    size++;    
  
  /////////////////////////////////////////////////////////////////////////////
  // Setup for drawing

  *p_data++ = GIF_TAG( size-1, 1, 0, 0, 0, 1 );
  *p_data++ = GIF_AD;

  *p_data++ = PbTextureGetTex0( pTex );
  *p_data++ = GS_TEX0_1+g_PbPrimContext;

  if( g_PbPrimAlphaEnable == TRUE )
  {
    *p_data++ = g_PbPrimAlpha;
    *p_data++ = GS_ALPHA_1+g_PbPrimContext;
  }

  *p_data++ = GS_SETREG_PRIM( GS_PRIM_PRIM_SPRITE, 0, 1, 0, g_PbPrimAlphaEnable, 
                              0, 1, g_PbPrimContext, 0) ;
  *p_data++ = GS_PRIM;

  *p_data++ = color;
  *p_data++ = GS_RGBAQ;

  *p_data++ = GS_SETREG_UV( u1, v1 );
  *p_data++ = GS_UV;

  *p_data++ = GS_SETREG_XYZ2( x1, y1, z );
  *p_data++ = GS_XYZ2;

  *p_data++ = GS_SETREG_UV( u2, v2 );
  *p_data++ = GS_UV;

  *p_data++ = GS_SETREG_XYZ2( x2, y2, z );
  *p_data++ = GS_XYZ2;
  
  PbDmaSend02Spr( p_store, size );
}

///////////////////////////////////////////////////////////////////////////////
// void PbPrimSpriteNoZtest
///////////////////////////////////////////////////////////////////////////////

void PbPrimSpriteNoZtest( int x1, int y1, int x2, int y2, int z, int color )
{
  u64* p_store;
  u64* p_data;
  int size = 7;

  x1 += 2048 << 4;
  y1 += 2048 << 4;
  x2 += 2048 << 4;
  y2 += 2048 << 4;

  p_store = p_data = PbSprAlloc( 8*16 );

  //////////////////////////////////////////////////////////////////////////////
  // Check if alpha is enabled

  if( g_PbPrimAlphaEnable == TRUE )
    size++;    
  
  /////////////////////////////////////////////////////////////////////////////
  // Setup for drawing

  *p_data++ = GIF_TAG( size-1, 1, 0, 0, 0, 1 );
  *p_data++ = GIF_AD;

  if( g_PbPrimAlphaEnable == TRUE )
  {
    *p_data++ = g_PbPrimAlpha;
    *p_data++ = GS_ALPHA_1+g_PbPrimContext;
  }

  *p_data++ = GS_SETREG_PRIM( GS_PRIM_PRIM_SPRITE, 0, 0, 0, g_PbPrimAlphaEnable,
                              0, 0, g_PbPrimContext, 0) ;
  *p_data++ = GS_PRIM;

  *p_data++ = GS_SETREG_TEST( 1, 7, 0xFF, 0, 0, 0, 1, 1 );     
  *p_data++ = GS_TEST_1+g_PbPrimContext;   

  *p_data++ = color;
  *p_data++ = GS_RGBAQ;

  *p_data++ = GS_SETREG_XYZ2( x1, y1, z );
  *p_data++ = GS_XYZ2;

  *p_data++ = GS_SETREG_XYZ2( x2, y2, z );
  *p_data++ = GS_XYZ2;

  *p_data++ = GS_SETREG_TEST( 1, 7, 0xFF, 0, 0, 0, 1, 2 );     
  *p_data++ = GS_TEST_1+g_PbPrimContext;     
  
  PbDmaSend02Spr( p_store, size );
}


////////////////////////////////////////////////////////////////////////////
// void PbPrimSetState
///////////////////////////////////////////////////////////////////////////////

void PbPrimSetState( PbPrimState State, int Value  )
{
  switch( State )
  {
    case PB_ALPHA_BLENDING : g_PbPrimAlphaEnable = Value; break;
  }
}

///////////////////////////////////////////////////////////////////////////////
// void PbPrimSetAlpha
///////////////////////////////////////////////////////////////////////////////

void PbPrimSetAlpha( u64 A, u64 B, u64 C, u64 D, u64 FIX )
{
  g_PbPrimAlpha = GS_SETREG_ALPHA( A, B, C, D, FIX );
}

///////////////////////////////////////////////////////////////////////////////
// void PbPrimSetAlpha
///////////////////////////////////////////////////////////////////////////////

void PbPrimSetContext( int State )
{
  g_PbPrimContext = State;
}

///////////////////////////////////////////////////////////////////////////////
// void PbPrimTriangleTexture
///////////////////////////////////////////////////////////////////////////////

void PbPrimTriangleTexture( PbTexture* pTex, int x1, int y1, int u1, int v1,  
                                             int x2, int y2, int u2, int v2,  
                                             int x3, int y3, int u3, int v3,  
                                             int z, int color  ) 
{ 
  u64* p_store; 
  u64* p_data; 
  int  size = 10;

  x1 += 2048 << 4; 
  y1 += 2048 << 4; 
  x2 += 2048 << 4; 
  y2 += 2048 << 4; 
  x3 += 2048 << 4; 
  y3 += 2048 << 4; 

  p_store = p_data = PbSprAlloc( 11*16 ); 

  if( g_PbPrimAlphaEnable == TRUE )
    size++;    
   
  *p_data++ = GIF_TAG( size-1, 1, 0, 0, 0, 1 ); 
  *p_data++ = GIF_AD; 

  *p_data++ = PbTextureGetTex0( pTex ); 
  *p_data++ = GS_TEX0_1+g_PbPrimContext; 

  if( g_PbPrimAlphaEnable == TRUE )
  {
    *p_data++ = g_PbPrimAlpha;
    *p_data++ = GS_ALPHA_1+g_PbPrimContext;
  }

  *p_data++ = GS_SETREG_PRIM( GS_PRIM_PRIM_TRIANGLE, 0, 1, 0, g_PbPrimAlphaEnable, 
                              0, 1, g_PbPrimContext, 0) ;
  *p_data++ = GS_PRIM; 

  *p_data++ = color; 
  *p_data++ = GS_RGBAQ; 

  *p_data++ = GS_SETREG_UV( u1, v1 ); 
  *p_data++ = GS_UV; 

  *p_data++ = GS_SETREG_XYZ2( x1, y1, z ); 
  *p_data++ = GS_XYZ2; 

  *p_data++ = GS_SETREG_UV( u2, v2 ); 
  *p_data++ = GS_UV; 

  *p_data++ = GS_SETREG_XYZ2( x2, y2, z ); 
  *p_data++ = GS_XYZ2; 
  
  *p_data++ = GS_SETREG_UV( u3, v3 ); 
  *p_data++ = GS_UV; 

  *p_data++ = GS_SETREG_XYZ2( x3, y3, z ); 
  *p_data++ = GS_XYZ2; 

  PbDmaSend02Spr( p_store, size ); 
}

///////////////////////////////////////////////////////////////////////////////
// void PbPrimQuadTextureGouraud
///////////////////////////////////////////////////////////////////////////////

void PbPrimQuadTextureGouraud(PbTexture* pTex, int x1, int y1, int u1, int v1,
                               int x2, int y2, int u2, int v2, 
                               int x3, int y3, int u3, int v3, 
                               int x4, int y4, int u4, int v4, int z,
                               int color1, int color2, int color3, int color4)
{
  u64* p_store;
  u64* p_data;
  int  size = 15;
  x1 += 2048 << 4;
  y1 += 2048 << 4;
  x2 += 2048 << 4;
  y2 += 2048 << 4;
  x3 += 2048 << 4;
  y3 += 2048 << 4;
  x4 += 2048 << 4;
  y4 += 2048 << 4;

  p_store = p_data = PbSprAlloc( 16*16 );

  //////////////////////////////////////////////////////////////////////////////
  // Check if alpha is enabled

  if( g_PbPrimAlphaEnable == TRUE )
    size++;    
  
  /////////////////////////////////////////////////////////////////////////////
  // Setup for drawing

  *p_data++ = GIF_TAG( size-1, 1, 0, 0, 0, 1 );
  *p_data++ = GIF_AD;

  *p_data++ = PbTextureGetTex0( pTex );
  *p_data++ = GS_TEX0_1+g_PbPrimContext;

  if( g_PbPrimAlphaEnable == TRUE )
  {
    *p_data++ = g_PbPrimAlpha;
    *p_data++ = GS_ALPHA_1+g_PbPrimContext;
  }

  *p_data++ = GS_SETREG_PRIM( GS_PRIM_PRIM_TRISTRIP, 1, 1, 0, g_PbPrimAlphaEnable, 
                              0, 1, g_PbPrimContext, 0) ;
  *p_data++ = GS_PRIM;

  *p_data++ = color1;
  *p_data++ = GS_RGBAQ;

  *p_data++ = GS_SETREG_UV( u1, v1 );
  *p_data++ = GS_UV;

  *p_data++ = GS_SETREG_XYZ2( x1, y1, z );
  *p_data++ = GS_XYZ2;

  *p_data++ = color2;
  *p_data++ = GS_RGBAQ;

  *p_data++ = GS_SETREG_UV( u2, v2 );
  *p_data++ = GS_UV;

  *p_data++ = GS_SETREG_XYZ2( x2, y2, z );
  *p_data++ = GS_XYZ2;

  *p_data++ = color3;
  *p_data++ = GS_RGBAQ;

  *p_data++ = GS_SETREG_UV( u3, v3 );
  *p_data++ = GS_UV;

  *p_data++ = GS_SETREG_XYZ2( x3, y3, z );
  *p_data++ = GS_XYZ2;

  *p_data++ = color4;
  *p_data++ = GS_RGBAQ;

  *p_data++ = GS_SETREG_UV( u4, v4 );
  *p_data++ = GS_UV;

  *p_data++ = GS_SETREG_XYZ2( x4, y4, z );
  *p_data++ = GS_XYZ2;
  
  PbDmaSend02Spr( p_store, size );
}

///////////////////////////////////////////////////////////////////////////////
// GifList settings and data
///////////////////////////////////////////////////////////////////////////////

#define PB_GIFLIST_MAXENTRIES 1024 

u64  PbGifList[PB_GIFLIST_MAXENTRIES*2] __attribute__((aligned(16))); 
u64* PbGifPtr = PbGifList; 
int  PbGifLength = 0; 

/////////////////////////////////////////////////////////////////////////////// 
// void PbGifListBegin 
/////////////////////////////////////////////////////////////////////////////// 

void PbGifListBegin() 
{ 
  PbGifPtr = PbGifList; 
  PbGifLength = 0; 
  PbGifListAdd( GIF_AD, 0 ); // tag set in  PbGifListSend 
} 

/////////////////////////////////////////////////////////////////////////////// 
// void PbGifListSend 
/////////////////////////////////////////////////////////////////////////////// 

void PbGifListSend() 
{ 
  PbGifList[0] = GIF_TAG( PbGifLength-1, 1, 0, 0, 0, 1 ); 
  FlushCache(0);
  PbDmaWait02(); 
  PbDmaSend02( PbGifList, PbGifLength ); 
}

