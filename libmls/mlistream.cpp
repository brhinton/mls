///////////////////////////////////////////////////////////////
//
//  $Id: mlistream.cpp,v 1.2 2002/05/18 21:26:23 alliz Exp $
//
//  MLStreams
//  Copyright (c) 2001-2002, Bryan Hinton
//  All rights reserved.
//
//  mlistream.cpp
//  Created by Bryan R. Hinton, on Wed Jul 04 2001, 17:44:54 CDT
//
//  Copyright (C) 2001
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
