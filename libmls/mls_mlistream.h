///////////////////////////////////////////////////////////////
// SPDX-License-Identifier: GPL-2.0-only
//
//  MLStreams
//  Copyright (c) 2001-2023, Bryan Hinton
//  All rights reserved.
//
//  mls_mlistream.h
//  Created by Bryan R. Hinton, on Wed Jul 04 2001, 19:50:20 CDT
//
//  File Contents: Interface and documentation of the mls_mlistream component.
//
///////////////////////////////////////////////////////////////

#ifndef MLSMLS_MLISTREAM_H
#define MLSMLS_MLISTREAM_H

#include <istream>

// linkage specifications: functions listed here will not be name encoded.
extern "C"
{}

namespace mls
{

   /** Purpose: TODO: Describe the purpose of the class.
    *  (Everything that you write here will show up in the
    *  doc++ generated documentation.)
    */

   template<class BufType>
   class mlistream : public StreamConfig<BufType, 0>::Base, public std::istream
   {
         typedef typename StreamConfig<BufType, 0>::Base Parent;

      public:
         /// Constructor.
         //explicit mlistream(int infd=0, int outfd = 1)  : Parent(infd, outfd), istream(rdbuf()){ }
         explicit mlistream(int infd=0)  : Parent(infd, -1), istream(rdbuf())
         { }

         ~mlistream()
         {  }

         BufType *rdbuf() const
         {
            return &buf;
         }

         BufType* operator->()
         {
            return rdbuf();
         }

      protected:

      private:
   };

#include "mls_mlistream.tcc"

} // End namespace mls

#endif

