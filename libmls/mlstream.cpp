///////////////////////////////////////////////////////////////
//
//  $Id: mlstream.cpp,v 1.2 2002/05/18 21:26:23 alliz Exp $
//
//  MLStreams
//  Copyright (c) 2001-2002, Bryan Hinton
//  All rights reserved.
//
//  mlstream.cpp
//  Created by Bryan R. Hinton, on Wed Jul 04 2001, 17:42:04 CDT
//
//  Copyright (C) 2001
//
//  File Contents: Implementation of the mlstream component.
//  Please see mlstream.h for full documentation of this system.
//
///////////////////////////////////////////////////////////////

#include "mlstream.h"

namespace mls
{

   template class mlstream<mlbuf>
   ;
   template class mlstream<mlpipebuf>
   ;
   template class mlstream<mlsockbuf>
   ;
   template class mlstream<mlshmbuf>
   ;

} // End namespace mls
