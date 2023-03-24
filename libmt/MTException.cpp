///////////////////////////////////////////////////////////////
// SPDX-License-Identifier: GPL-2.0-only
//
//  MLStreams
//  Copyright (c) 2001-2023, Bryan Hinton
//  All rights reserved.
//
//  MTException.cpp
//  Created by Bryan R. Hinton, on Mon Jul 02 2001, 17:35:31 CDT
//
//  File Contents: Implementation of the MTException component.
//  Please see MTException.h for full documentation of this system.
//
///////////////////////////////////////////////////////////////

#include "MTException.h"

namespace MTLib
{

   ///////////////////////////////////////////////////////////////
   // MTException implementation.
   ///////////////////////////////////////////////////////////////
   MTException::MTException(int rval) throw() : ecode(rval)
   {
      msg[0]='\0';
   }

   MTException::MTException(int rval, const char *message) throw() : ecode(rval)
   {
      strncpy(msg, message, MSGBUFSIZE);
   }

   MTException::MTException(const char *message) throw() : ecode(0)
   {
      strncpy(msg, message, MSGBUFSIZE);
   }

   MTException::MTException(const MTException &copy) throw()
   {
      ecode = copy.ecode;
      strncpy(msg, copy.msg, MSGBUFSIZE);
   }

   const MTException&
   MTException::operator=(const MTException &rhs) throw()
   {
      if(this != &rhs) {
         ecode = rhs.ecode;
         strncpy(msg, rhs.msg, MSGBUFSIZE);
      }
      return(*this);
   }

} // End namespace MTLib
