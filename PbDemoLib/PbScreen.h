/*
 * PbScreen.h - Screen handling functions for Pb demo library
 *
 * Copyright (c) 2004   emoon <daniel@collin.com>
 *
 * Licensed under the AFL v2.0. See the file LICENSE included with this
 * distribution for licensing terms.
 */

#ifndef _PBSCREEN_H_
#define _PBSCREEN_H_

#include <tamtypes.h>

///////////////////////////////////////////////////////////////////////////////
// Functions
///////////////////////////////////////////////////////////////////////////////

void PbScreenSetup( int Width,int Height,int PSM );
void PbScreenSyncFlip();

int PbScreenGetOffsetX();
int PbScreenGetOffsetY();

void PbScreenClear( int Color );

void PbScreenSetCurrentActive();

///////////////////////////////////////////////////////////////////////////////
// Debug functions
///////////////////////////////////////////////////////////////////////////////

void PbScreenDisplayAt( u32 Pos, int Width );

///////////////////////////////////////////////////////////////////////////////
// Internal functions
///////////////////////////////////////////////////////////////////////////////

void PbScreenVsync();
void PbScreenFlip();
void PbScreenSetActive( int Buffer );
int  PbScreenGetActive();

#endif // _PBSCREEN_H_


