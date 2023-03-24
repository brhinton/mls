///////////////////////////////////////////////////////////////
//  SPDX-License-Identifier: GPL-2.0-only
//
//  MLStreams
//  Copyright (c) 2001-2023, Bryan Hinton
//  All rights reserved.
//
//  Mutex.h
//  Created by Bryan R. Hinton, on Mon Jul 02 2001, 17:35:07 CDT
//
//  File Contents: Interface and documentation of the Mutex component.
//
///////////////////////////////////////////////////////////////

#ifndef MTLIBMUTEX_H
#define MTLIBMUTEX_H


// linkage specifications: functions listed here will not be name encoded.
extern "C"
{}

#include "MutexAttr.h"


namespace MTLib
{

   /** Purpose: TODO: Describe the purpose of the class.
    *  (Everything that you write here will show up in the
    *  doc++ generated documentation.)
    */
   class Mutex
   {

      public:
         /// Constructor.
         Mutex();

         // Copy Constructor.
         Mutex(const Mutex&);

         // Destructor.
         virtual ~Mutex();

         // Overloaded Assignment Operator.
         const Mutex& operator=(const Mutex&);

         /// DumpDiagnostics() dumps the object's state to standard output.
         void DumpDiagnostics() const;

         virtual int Init(MutexAttr &) = 0;
         virtual void Destroy(void) = 0;
         virtual int Lock(void) = 0;
         virtual int unLock(void) = 0;
         virtual int tryLock(void) = 0;
         virtual pthread_mutex_t * getLock(void) = 0;
         virtual pthread_mutex_t * operator&(void) = 0;


         // probably shouldnt support pthread_mutex_attr_settype
         // in derived classes as each derived class is a type of mutex

         //Realtime Thread support
         //virtual int setPrioCeiling(int, int *) = 0;
         //virtual int getPrioCeiling(int *) = 0;

      protected:

      private:

   }
   ; // End class Mutex

} // End namespace MTLib

#endif

