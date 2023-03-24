///////////////////////////////////////////////////////////////
//  SPDX-License-Identifier: GPL-2.0-only
//
//  CondAttr.h
//  Created by Bryan R. Hinton, on Mon Jul 02 2001, 17:34:03 CDT
//
//  Copyright (C) 2001-2023
//
//  Permission is granted to use this code without restriction,
//  as long as this copyright notice appears in all source files.
//
//
//  File Contents: Interface and documentation of the CondAttr component.
//
///////////////////////////////////////////////////////////////

#ifndef MTLIBCONDATTR_H
#define MTLIBCONDATTR_H



// linkage specifications: functions listed here will not be name encoded.
extern "C"
{
#include <pthread.h>
}

namespace MTLib
{

   /** Purpose: TODO: Describe the purpose of the class.
    *  (Everything that you write here will show up in the
    *  doc++ generated documentation.)
    */
   class CondAttr
   {

      public:
         /// Constructor.
         CondAttr();

         // Copy Constructor.
         CondAttr(const CondAttr&);

         // Destructor.
         virtual ~CondAttr();

         // Overloaded Assignment Operator.
         const CondAttr& operator=(const CondAttr&);

         /// DumpDiagnostics() dumps the object's state to standard output.
         void DumpDiagnostics() const;

         pthread_condattr_t* operator&(void);


      protected:

      private:
         int Init(void);
         void Destroy(void);

         pthread_condattr_t cattr;

   }
   ; // End class CondAttr

} // End namespace MTLib

#endif

