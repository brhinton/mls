///////////////////////////////////////////////////////////////
//  SPDX-License-Identifier: GPL-2.0-only
//
//  MLStreams
//  Copyright (c) 2001-2023, Bryan Hinton
//  All rights reserved.
//
//  mlstream.h
//  Created by Bryan R. Hinton, on Wed Jul 04 2001, 17:42:04 CDT
//
//  File Contents: Interface and documentation of the mlstream component.
//
///////////////////////////////////////////////////////////////

#ifndef MLSMLSTREAM_H
#define MLSMLSTREAM_H


// linkage specifications: functions listed here will not be name encoded.
extern "C"
{}

#include "mlistream.h"
#include "mlostream.h"
#include "mls_mlstream.h"

namespace mls
{

   // typedefs for 4 different types of streams
   // each declaration instantiates a stream
   // that is specializes for a specific type of internal
   // buffer

   typedef mlstream<mlbuf> txtstream;
   typedef mlstream<mlpipebuf> pipestream;
   typedef mlstream<mlshmbuf> shmstream;
   typedef mlstream<mlsockbuf> sockstream;

} // End namespace mls

#endif

