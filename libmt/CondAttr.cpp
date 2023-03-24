///////////////////////////////////////////////////////////////
//  SPDX-License-Identifier: GPL-2.0-only
//
//  MLStreams
//  Copyright (c) 2001-2023, Bryan Hinton
//  All rights reserved.
//
//  CondAttr.cpp
//  Created by Bryan R. Hinton, on Mon Jul 02 2001, 17:34:03 CDT
//
//  File Contents: Implementation of the CondAttr component.
//  Please see CondAttr.h for full documentation of this system.
//
///////////////////////////////////////////////////////////////

#include "CondAttr.h"


namespace MTLib
{

   CondAttr::CondAttr()
   {
      int ret = Init();
   }

   CondAttr::CondAttr(const CondAttr &copy)
   {}

   CondAttr::~CondAttr()
   {
      Destroy();
   }

   const CondAttr&
   CondAttr::operator=(const CondAttr &rhs)
   {}

   void
   CondAttr::DumpDiagnostics() const
   {
      //std::cout << std::endl << std::endl <<
      //"CondAttr Diagnostics dump "<< std::endl << std::endl;
   }

   pthread_condattr_t*
   CondAttr::operator&(void)
   {
      return (&cattr);
   }

   int
   CondAttr::Init(void)
   {
      return( pthread_condattr_init(&cattr) );
   }

   void
   CondAttr::Destroy(void)
   {
      pthread_condattr_destroy(&cattr);
   }



} // End namespace MTLib
