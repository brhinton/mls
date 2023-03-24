///////////////////////////////////////////////////////////////
//  SPDX-License-Identifier: GPL-2.0-only
//
//  MLStreams
//  Copyright (c) 2001-2023, Bryan Hinton
//  All rights reserved.
//
//  mlistream.cpp
//  Created by Bryan R. Hinton, on Wed Jul 04 2001, 17:44:54 CDT
//
//  File Contents: Implementation of the mlistream component.
//  Please see mlistream.h for full documentation of this system.
//
///////////////////////////////////////////////////////////////

#include "mlistream.h"

namespace mls
{

   // instantiations
   template class mlistream<mlbuf>
   ;
   template class mlistream<mlpipebuf>
   ;
   template class mlistream<mlsockbuf>
   ;
   template class mlistream<mlshmbuf>
   ;

} // End namespace mls
