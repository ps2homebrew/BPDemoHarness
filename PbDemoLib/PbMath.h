/*
 * PbMath.h - Math functions for Pb demo library
 *
 * Copyright (c) 2004   emoon <daniel@collin.com>
 *
 * Licensed under the AFL v2.0. See the file LICENSE included with this
 * distribution for licensing terms.
 */

#ifndef _PBMATH_H_
#define _PBMATH_H_

///////////////////////////////////////////////////////////////////////////////
// defines
///////////////////////////////////////////////////////////////////////////////

#ifndef M_PI
#define M_PI 3.14159265358979323846f
#endif

#define SIN_ITERATOR 20

#define PB_RAND_MAX 0x7fff

///////////////////////////////////////////////////////////////////////////////
// Functions
///////////////////////////////////////////////////////////////////////////////

float PbSin( float angle );
float PbCos( float angle );
float PbSqrt( float value );
int   PbLog( int Value );
int   PbRand();

#endif // _PBMATH_H_


