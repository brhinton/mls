///////////////////////////////////////////////////////////////
//
//  $Id: FastMutex.h,v 1.3 2002/05/18 21:30:16 alliz Exp $
//
//  MLStreams
//  Copyright (c) 2001-2002, Bryan Hinton
//  All rights reserved.
//
//  FastMutex.h
//  Created by Bryan R. Hinton, on Mon Jul 02 2001, 17:34:25 CDT
//
//  Copyright (C) 2001
//
//  File Contents: Interface and documentation of the FastMutex component.
//
///////////////////////////////////////////////////////////////

#ifndef MTLIBFASTMUTEX_H
#define MTLIBFASTMUTEX_H


// linkage specifications: functions listed here will not be name encoded.
extern "C"
{
#include <unistd.h>
	#include <limits.h>
}

#include "Mutex.h"

namespace MTLib
{

   /** Purpose: TODO: Describe the purpose of the class.
    *  (Everything that you write here will show up in the
    *  doc++ generated documentation.)
    */
   class FastMutex : public Mutex
   {

      public:
         /// Constructor.
         FastMutex();
         FastMutex(MutexAttr &);

         // Copy Constructor.
         FastMutex(const FastMutex&);

         // Destructor.
         virtual ~FastMutex();

         // Overloaded Assignment Operator.
         const FastMutex& operator=(const FastMutex&);

         /// DumpDiagnostics() dumps the object's state to standard output.
         void DumpDiagnostics() const;



         virtual int Init(MutexAttr &);
         virtual void Destroy(void);
         virtual int Lock(void);
         virtual int unLock(void);
         virtual int tryLock(void);
         virtual pthread_mutex_t * getLock(void);
         virtual pthread_mutex_t * operator&(void);

         //virtual int getType(void) = 0;
#ifdef XOPEN_REALTIME
         // set / get priority ceiling of mutex
         int
         setPrioceiling(int, int*);

         int
         getPrioceiling(int*);
#endif

      protected:
         pthread_mutex_t mlock;

      private:

   }
   ; // End class FastMutex

} // End namespace MTLib

#endif

