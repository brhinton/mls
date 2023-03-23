///////////////////////////////////////////////////////////////
//
//  $Id: mlostream.cpp,v 1.2 2002/05/18 21:26:23 alliz Exp $
//
//  MLStreams
//  Copyright (c) 2001-2002, Bryan Hinton
//  All rights reserved.
//
//  mlostream.cpp
//  Created by Bryan R. Hinton, on Wed Jul 04 2001, 17:47:01 CDT
//
//  Copyright (C) 2001
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
