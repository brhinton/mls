///////////////////////////////////////////////////////////////
//
//  $Id: CV.h,v 1.3 2002/05/18 21:30:16 alliz Exp $
//
//  MLStreams
//  Copyright (c) 2001-2002, Bryan Hinton
//  All rights reserved.
//
//  CV.h
//  Created by Bryan R. Hinton, on Mon Jul 02 2001, 17:33:13 CDT
//
//  Copyright (C) 2001
//
//  File Contents: Interface and documentation of the CV component.
//
///////////////////////////////////////////////////////////////

#ifndef MTLIBCV_H
#define MTLIBCV_H

// linkage specifications: functions listed here will not be name encoded.
extern "C"
{}

#include "CondAttr.h"
#include "Mutex.h"

namespace MTLib
{

   /** Purpose: TODO: Describe the purpose of the class.
    *  (Everything that you write here will show up in the
    *  doc++ generated documentation.)
    */
   class CV
   {

      public:
         /// Constructor.
         CV();
         CV(CondAttr &);

         // Copy Constructor.
         CV(const CV&);

         // Destructor.
         virtual ~CV();

         // Overloaded Assignment Operator.
         const CV& operator=(const CV&);

         /// DumpDiagnostics() dumps the object's state to standard output.
         void DumpDiagnostics() const;

         int
         Init(CondAttr &);

         void
         Destroy(void);

         int
         Wait(Mutex &);

         int
         timedWait(Mutex *m, const struct timespec *abstime);

         int
         Signal(void);

      protected:

      private:
         pthread_cond_t cvar;

   }
   ; // End class CV

} // End namespace MTLib

#endif

