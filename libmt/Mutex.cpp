///////////////////////////////////////////////////////////////
//
//  $Id: Mutex.cpp,v 1.3 2002/05/18 21:30:16 alliz Exp $
//
//  MLStreams
//  Copyright (c) 2001-2002, Bryan Hinton
//  All rights reserved.
//
//  Mutex.cpp
//  Created by Bryan R. Hinton, on Mon Jul 02 2001, 17:35:07 CDT
//
//  Copyright (C) 2001
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
