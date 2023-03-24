///////////////////////////////////////////////////////////////
//  SPDX-License-Identifier: GPL-2.0-only
//
//  MLStreams
//  Copyright (c) 2001-2023, Bryan Hinton
//  All rights reserved.
//
//  mlshmstreamimpl.h
//  Created by Bryan R. Hinton, on Wed Jul 04 2001, 20:09:33 CDT
//
//  File Contents: Interface and documentation of the mlshmstreamimpl component.
//
///////////////////////////////////////////////////////////////

#ifndef MLSMLSHMSTREAMIMPL_H
#define MLSMLSHMSTREAMIMPL_H

#include "mlstreamimpl.h"
#include "mlshmbuf.h"

// linkage specifications: functions listed here will not be name encoded.
extern "C"
{}

namespace mls
{

   template<class BufType, int direction>
   class mlstreamimpl<BufType, direction, mlshmbuf> : public StreamConfig<BufType, direction, mlbuf>::Base
   {
         typedef typename StreamConfig<BufType, direction, mlbuf>::Base Parent;

      public:
         mlstreamimpl() : Parent()
         {
#ifdef DEBUG
            char *fname = "mlstreamimpl<Impl, direction, Shm>() : Parent()";
            Trace T(fname);
#endif

         }

         mlstreamimpl(int infd, int outfd)
               : Parent(infd, outfd)
         {
#ifdef DEBUG
            char *fname = "mlstreamimpl<Impl, direction, Shm>(int infd, int outfd) : Parent(infd, oufd)";
            Trace T(fname);
#endif

         }

         ~mlstreamimpl()
         {
#ifdef DEBUG
            char *fname = "virtual ~mlstreamimpl<mlshmbuf>()";
            Trace T(fname);
#endif

         }

         int open()//(const char *path, int oflag, mode_t mode)
         {
#ifdef DEBUG
            char *fname="mlstreamimpl<mlshmbuf>::open(const char *path, int oflag, mode_t mode)";
            Trace T(fname);
#ifdef RTTIDEBUG
            //make sure the correct derived function is getting called
            t.debug( (typeid(*this).name()) );
#endif
				#endif

            return 0;
         }
         int close()
         {
#ifdef DEBUG
            char *fname="mlstreamimpl<mlshmbuf>::close()";
            //cout << typeid(*this).name();
            Trace t(fname);
#endif

            return 0;
         }
         //stat
         int stat()
         {
#ifdef DEBUG
            char *fname="mlstreamimpl<mlshmbuf>::stat()";
            //cout << typeid(*this).name();
            Trace t(fname);
#endif

            return 0;
         }
   };

   template<class Parent>
   class mlinputimpl<Parent, mlshmbuf> : public Parent
   {
      public:
         mlinputimpl() : Parent()
         { }

         mlinputimpl(int infd, int outfd) : Parent(infd, outfd)
         {
#ifdef DEBUG
            char *fname = "mlinputimpl<Parent, Shm>(int infd, int outfd) : Parent(infd, outfd)";
            Trace T(fname);
#endif

         }

         int pread()
         {
            return 0;
         }

         int readv()
         {
#ifdef DEBUG
            char *fname="mlistreamimpl<shmbuf>::readv()";
            //cout << typeid(*this).name();
            Trace t(fname);
#endif

            return 0;
         }

         int read()
         {
#ifdef DEBUG
            char *fname="mlistreamimpl<mlshmbuf>::read()";
            Trace t(fname);
#endif

            return 0;
         }
   };

   template<class Parent>
   class mloutputimpl<Parent, mlshmbuf> : public Parent
   {
      public:
         mloutputimpl() : Parent()
         {}
         mloutputimpl(int infd, int outfd) : Parent(infd, outfd)
         {
#ifdef DEBUG
            char *fname = "mloutputimpl<Parent, Sock>(int infd, int outfd) : Parent(infd, outfd)";
            Trace T(fname);
#endif

         }
         int pwrite()
         {
            return 0;
         }
         int writev()
         {
            return 0;
         }

         int write()
         {
            return 0;
         }
   };

#include "mlshmstreamimpl.tcc"

} // End namespace mls

#endif

