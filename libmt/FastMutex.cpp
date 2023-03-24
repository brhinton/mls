///////////////////////////////////////////////////////////////
//  SPDX-License-Identifier: GPL-2.0-only
//
//  MLStreams
//  Copyright (c) 2001-2023, Bryan Hinton
//  All rights reserved.
//
//  FastMutex.cpp
//  Created by Bryan R. Hinton, on Mon Jul 02 2001, 17:34:25 CDT
//
//  File Contents: Implementation of the FastMutex component.
//  Please see FastMutex.h for full documentation of this system.
//
///////////////////////////////////////////////////////////////

#include "FastMutex.h"


namespace MTLib
{

   FastMutex::FastMutex()
   {
      MutexAttr Mattr;
      int ret = Init(Mattr);
   }

   FastMutex::FastMutex(MutexAttr &Mattr)
   {
      int ret = Init(Mattr);
   }

   FastMutex::FastMutex(const FastMutex &copy)
   {}

   FastMutex::~FastMutex()
   {
      Destroy();
   }

   const FastMutex&
   FastMutex::operator=(const FastMutex &rhs)
   {}

   void
   FastMutex::DumpDiagnostics() const
   {
      //std::cout << std::endl << std::endl <<
      //"FastMutex Diagnostics dump "<< std::endl << std::endl;
   }

   int
   FastMutex::Init(MutexAttr &Mattr)
   {
      int ret = pthread_mutex_init(&mlock, &Mattr);
   }

   void
   FastMutex::Destroy(void)
   {
      pthread_mutex_destroy(&mlock);
   }

   int
   FastMutex::Lock(void)
   {
      return( pthread_mutex_lock(&mlock) );
   }

   int
   FastMutex::unLock(void)
   {
      return( pthread_mutex_unlock(&mlock) );
   }

   int
   FastMutex::tryLock(void)
   {
      return( pthread_mutex_trylock(&mlock) );
   }

   pthread_mutex_t*
   FastMutex::getLock(void)
   {
      return( &mlock );
   }

#ifdef XOPEN_REALTIME
   int
   FastMutex::setPrioceiling(int prioceiling, int *oldceiling)
   {
      return ( pthread_mutex_setprioceiling(&mlock, prioceiling, oldceiling) );
   }

   int
   FastMutex::getPrioceiling(int *prioceiling)
   {
      return ( pthread_mutex_getprioceiling(&mlock, prioceiling) ) ;
   }

#endif


   pthread_mutex_t*
   FastMutex::operator&(void)
   {
      return( &mlock );
   }
} // End namespace MTLib
