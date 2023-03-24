///////////////////////////////////////////////////////////////
// SPDX-License-Identifier: GPL-2.0-only
//
//  MLStreams
//  Copyright (c) 2001-2023, Bryan Hinton
//  All rights reserved.
//
//  mlostream.h
//  Created by Bryan R. Hinton, on Wed Jul 04 2001, 17:47:01 CDT
//
//  File Contents: Interface and documentation of the mlostream component.
//
///////////////////////////////////////////////////////////////

#ifndef MLSMLOSTREAM_H
#define MLSMLOSTREAM_H

// linkage specifications: functions listed here will not be name encoded.
extern "C"
{}

#include "mlsockstreamimpl.h"
#include "mlshmstreamimpl.h"
#include "mls_mlostream.h"

namespace mls
{

   // typedefs for 4 different types of output streams
   // each declaration instantiates an outpustream
   // that is specialized for a specific type of internal
   // output buffer
   typedef mlostream<mlbuf> otxtstream;
   typedef mlostream<mlpipebuf> opipestream;
   typedef mlostream<mlsockbuf> osockstream;
   typedef mlostream<mlshmbuf> oshmstream;

} // End namespace mls

#endif

