///////////////////////////////////////////////////////////////
// SPDX-License-Identifier: GPL-2.0-only
//
//  MLStreams
//  Copyright (c) 2001-2023, Bryan Hinton
//  All rights reserved.
//
//  mlostream.cpp
//  Created by Bryan R. Hinton, on Wed Jul 04 2001, 17:47:01 CDT
//
//  File Contents: Implementation of the mlostream component.
//  Please see mlostream.h for full documentation of this system.
//
///////////////////////////////////////////////////////////////

#include "mlostream.h"

namespace mls
{

   // instantiations
   template class mlostream<mlbuf>
   ;
   template class mlostream<mlpipebuf>
   ;
   template class mlostream<mlsockbuf>
   ;
   template class mlostream<mlshmbuf>
   ;

} // End namespace mls
