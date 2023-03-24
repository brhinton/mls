///////////////////////////////////////////////////////////////
// SPDX-License-Identifier: GPL-2.0-only
//
//  MLStreams
//  Copyright (c) 2001-2023, Bryan Hinton
//  All rights reserved.
//
//  mlistream.h
//  Created by Bryan R. Hinton, on Wed Jul 04 2001, 17:44:54 CDT
//
//  File Contents: Interface and documentation of the mlistream component.
//
///////////////////////////////////////////////////////////////

#ifndef MLSMLISTREAM_H
#define MLSMLISTREAM_H

// linkage specifications: functions listed here will not be name encoded.
extern "C"
{}

#include "mlsockstreamimpl.h"
#include "mlshmstreamimpl.h"
#include "mls_mlistream.h"

namespace mls
{

   // typedefs for four different types of input streams
   // each declaration instantiates an inputstream
   // that is specialized for a specific type of internal
   // input buffer
   typedef mlistream<mlbuf> itxtstream;
   typedef mlistream<mlpipebuf> ipipestream;
   typedef mlistream<mlsockbuf> isockstream;
   typedef mlistream<mlshmbuf> ishmstream;

} // End namespace mls

#endif

