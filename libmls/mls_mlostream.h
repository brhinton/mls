///////////////////////////////////////////////////////////////
//
//  $Id: mls_mlostream.h,v 1.3 2002/05/18 21:26:23 alliz Exp $
//
//  MLStreams
//  Copyright (c) 2001-2002, Bryan Hinton
//  All rights reserved.
//
//  mls_mlostream.h
//  Created by Bryan R. Hinton, on Wed Jul 04 2001, 19:50:25 CDT
//
//  Copyright (C) 2001
//
//  File Contents: Interface and documentation of the mls_mlostream component.
//
///////////////////////////////////////////////////////////////


#include <ostream>


#ifndef MLSMLS_MLOSTREAM_H
#define MLSMLS_MLOSTREAM_H



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
   class mlostream : public StreamConfig<BufType, 1>::Base, public std::ostream
   {
         typedef typename StreamConfig<BufType, 1>::Base Parent;

      public:
         /// Constructor.
         //explicit mlostream(int infd=0, int outfd = 1)  : Parent(infd, outfd), ostream(rdbuf()){ }
         explicit mlostream(int outfd = 1)  : Parent(-1, outfd), ostream(rdbuf())
         { }

         ~mlostream()
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

#include "mls_mlostream.tcc"

} // End namespace mls

#endif

