///////////////////////////////////////////////////////////////
//  SPDX-License-Identifier: GPL-2.0-only
//
//  MLStreams
//  Copyright (c) 2001-2023, Bryan Hinton
//  All rights reserved.
//
//  mls_mlstream.h
//  Created by Bryan R. Hinton, on Wed Jul 04 2001, 19:50:14 CDT
//
//  File Contents: Interface and documentation of the mls_mlstream component.
//
///////////////////////////////////////////////////////////////

#ifndef MLSMLS_MLSTREAM_H
#define MLSMLS_MLSTREAM_H

#include <iostream>

// linkage specifications: functions listed here will not be name encoded.
extern "C"
{}

namespace mls
{

   template<class BufType>
   class mlstream;

   class StreamVisitor
   {

      public:
         virtual void Visit(mlstream<mlbuf> &str)
         {}
         virtual void Visit(mlstream<mlpipebuf> &str)
         {}
         virtual void Visit(mlstream<mlsockbuf> &str)
         {}
         virtual void Visit(mlstream<mlshmbuf> &str)
         {}
   }
   ;

   class StreamStateVisitor : public StreamVisitor
   {

      public:
         void Visit(mlstream<mlbuf> &str)
         {
            cout << "streamstatevisitor mlbuf" << endl;
         }
         void Visit(mlstream<mlpipebuf> &str)
         {
            cout << "streamstatevisitor mlpipebuf" << endl;
         }
         void Visit(mlstream<mlsockbuf> &str)
         {
            cout << "streamstatevisitor mlpipebuf" << endl;
         }
         void Visit(mlstream<mlshmbuf> &str)
         {
            cout << "streamstatevisitor mlpipebuf" << endl;
         }
   };

   /** Purpose: TODO: Describe the purpose of the class.
       *  (Everything that you write here will show up in the
       *  doc++ generated documentation.)
       */
   template<class BufType>
   class mlstream : public StreamConfig<BufType, 10>::Base, public std::iostream
   {

         typedef typename StreamConfig<BufType, 10>::Base Parent;

      public:
         /// Constructor.
         explicit
         mlstream(int infd, int outfd)  : Parent(infd, outfd), iostream(rdbuf())
         {  }

         ~mlstream()
         {  }

         BufType
         *rdbuf() const
         {
            return &buf;
         }

         BufType*
         operator->()
         {
            return rdbuf();
         }

         void Accept(StreamVisitor &v)
         {
            v.Visit(*this);
         }

      protected:

      private:
   };

#include "mls_mlstream.tcc"

} // End namespace mls

#endif

