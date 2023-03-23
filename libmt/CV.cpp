///////////////////////////////////////////////////////////////
//
//  $Id: CV.cpp,v 1.3 2002/05/18 21:30:15 alliz Exp $
//
//  MLStreams
//  Copyright (c) 2001-2002, Bryan Hinton
//  All rights reserved.
//
//  CV.cpp
//  Created by Bryan R. Hinton, on Mon Jul 02 2001, 17:33:13 CDT
//
//  Copyright (C) 2001
//
//
//  File Contents: Implementation of the CV component.
//  Please see CV.h for full documentation of this system.
//
///////////////////////////////////////////////////////////////

#include "CV.h"


namespace MTLib
{

   CV::CV()
   {
      CondAttr Cattr;
      int ret = Init(Cattr);
   }

   CV::CV(CondAttr  &Cattr)
   {
      int ret = Init(Cattr);
   }

   CV::CV(const CV &copy)
   {}

   CV::~CV()
   {
      Destroy();
   }

   const CV&
   CV::operator=(const CV &rhs)
   {}

   void
   CV::DumpDiagnostics() const
   {
      //std::cout << std::endl << std::endl <<
      //"CV Diagnostics dump "<< std::endl << std::endl;
   }

   int
   CV::Init(CondAttr &Cattr)
   {
      return( pthread_cond_init(&cvar, &Cattr) );
   }

   void
   CV::Destroy(void)
   {
      pthread_cond_destroy(&cvar);
   }

   int
   CV::Wait(Mutex &MLock)
   {
      return( pthread_cond_wait(&cvar, &MLock) );
   }

   int
   CV::timedWait(Mutex *m, const struct timespec *abstime)
   {
      return( pthread_cond_timedwait(&cvar, m->operator&(), abstime) );
   }

   int
   CV::Signal(void)
   {
      return( pthread_cond_signal(&cvar) ) ;
   }

} // End namespace MTLib
