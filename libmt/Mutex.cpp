///////////////////////////////////////////////////////////////
//  SPDX-License-Identifier: GPL-2.0-only
//
//  MLStreams
//  Copyright (c) 2001-2023, Bryan Hinton
//  All rights reserved.
//
//  Mutex.cpp
//  Created by Bryan R. Hinton, on Mon Jul 02 2001, 17:35:07 CDT
//
//  File Contents: Implementation of the Mutex component.
//  Please see Mutex.h for full documentation of this system.
//
///////////////////////////////////////////////////////////////

#include "Mutex.h"


namespace MTLib
{

   Mutex::Mutex()
   {}

   Mutex::Mutex(const Mutex &copy)
   {}

   Mutex::~Mutex()
   {}

   const Mutex&
   Mutex::operator=(const Mutex &rhs)
   {}

   void
   Mutex::DumpDiagnostics() const
   {
      //std::cout << std::endl << std::endl <<
      //"Mutex Diagnostics dump "<< std::endl << std::endl;
   }


} // End namespace MTLib
