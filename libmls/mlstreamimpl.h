///////////////////////////////////////////////////////////////
//  SPDX-License-Identifier: GPL-2.0-only
//
//  MLStreams
//  Copyright (c) 2001-2023, Bryan Hinton
//  All rights reserved.
//
//  mlstreamimpl.h
//  Created by Bryan R. Hinton, on Wed Jul 04 2001, 20:08:54 CDT
//
//  File Contents: Interface and documentation of the mlstreamimpl component.
//
///////////////////////////////////////////////////////////////

#ifndef MLSMLSTREAMIMPL_H
#define MLSMLSTREAMIMPL_H


// linkage specifications: functions listed here will not be name encoded.
extern "C"
{}

#include "StreamConfig.h"

namespace mls
{

   ///////////////////////////////////////////////////////////////
   // --- MLSTREAMIMPL ---
   //
   // This class defines the generic/base implementation for
   // a generic mlstream of type BufferType
   ///////////////////////////////////////////////////////////////
   template<class BufType, int direction, class BaseType>
   class mlstreamimpl //: public mlstreambase<Impl>
   {
      protected:
         mutable BufType buf;

      public:
         mlstreamimpl() : buf()
         {
#ifdef DEBUG
            char *fname = "mlstreamimpl<Impl, direction, TYPE>() : mlstreambase<Impl>()";
            Trace T(fname);
#endif

         }

         mlstreamimpl(int infd, int outfd) : buf(infd, outfd)
         {
#ifdef DEBUG
            char *fname = "mlstreamimpl<Impl, direction, TYPE>(int infd, int outfd) : mlstreambase<Impl>";
            Trace T(fname);
#endif

         }

         ~mlstreamimpl()
         {
#ifdef DEBUG
            char *fname = "virtual ~mlstreamimpl()";
            Trace T(fname);
#endif

         }

         //int open()//(const char *path, int oflag, mode_t mode)
         int
         open( const char *path, int oflag, mode_t mode)
         {
#ifdef DEBUG
            char *fname="mlstreamimpl<BufferType>::open(const char *path, int oflag, mode_t mode)";
            Trace T(fname);
#ifdef RTTIDEBUG
            //make sure the correct derived function is getting called
            t.debug( (typeid(*this).name()) );
#endif
				#endif

            //fix to set state
            return buf.ml_open(path, oflag, mode);
         }

         int
         close()
         {
#ifdef DEBUG
            char *fname="mlstreamimpl<BufferType>::close()";
            //cout << typeid(*this).name();
            Trace t(fname);
#endif

            return buf.ml_close();

            return 0;
         }

         //----------------------
         // stat methods - use pathname and file descriptor
         // already stored

         //stat
         // obtain info about the file represented
         // by file pathname contained in internal streambuf
         int
         stat(struct stat *buf)
         {
#ifdef DEBUG
            char *fname="mlstreamimpl<BufferType>::stat()";
            //cout << typeid(*this).name();
            Trace t(fname);
#endif

            return ml_stat(buf);
         }

         // lstat
         // obtain information about symbolic link
         // represented by file pathname contained
         // in internal streambuf
         int
         lstat(struct stat *buf)
         {
            return ml_lstat(buf);
         }

         // fstat
         // obtain info about open file descriptor contained
         // in internal streambuf
         int
         fstat(struct stat *buf)
         {
            return ml_fstat(buf);
         }
         //------------------------

         int
         attach(int fd)
         {
            //return buf.ml_attach(fd);
            buf.ml_attach(fd);
            return 0;
         }
   };

   ///////////////////////////////////////////////////////////////
   //				--MLINPUTIMPL--
   ///////////////////////////////////////////////////////////////
   template<class Parent, class BaseType>
   class mlinputimpl : public Parent
   {
      public:
         mlinputimpl() : Parent()
         {}

         mlinputimpl(int infd, int outfd) : Parent(infd, outfd)
         {
#ifdef DEBUG
            char *fname = "mlinputimpl<Parent, Type>(int infd, int outfd) : Parent(infd, outfd)";
            Trace T(fname);
#endif

         }

         int
         pread()
         {
            return 0;
         }

         int
         readv()
         {
#ifdef DEBUG
            char *fname="mlistreamimpl<BufferType>::readv()";
            //cout << typeid(*this).name();
            Trace t(fname);
#endif

            return 0;
         }

         int
         read()
         {
#ifdef DEBUG
            char *fname="mlistreamimpl<BufferType>::read()";
            //cout << typeid(*this).name();
            Trace t(fname);
#endif

            return 0;
         }
   };
   ///////////////////////////////////////////////////////////////
   //
   // --MLOUTPUTIMPL--
   //
   ///////////////////////////////////////////////////////////////
   template<class Parent, class BaseType>
   class mloutputimpl : public Parent
   {
      public:
         mloutputimpl() : Parent()
         {
#ifdef DEBUG
            char *fname = "mloutputimpl<Parent, TYPE>()";
            Trace T(fname);
#endif

         }

         mloutputimpl(int infd, int outfd) : Parent(infd, outfd)
         {
#ifdef DEBUG
            char *fname = "mloutputimpl<Parent, Type>(int infd, int outfd) : Parent(infd, outfd)";
            Trace T(fname);
#endif

         }

         int
         pwrite()
         {
#ifdef DEBUG
            char *fname = "mloutputimpl<Parent, Type>::pwrite()";
            Trace T(fname);
#endif

            return 0;
         }

         int
         writev()
         {
#ifdef DEBUG
            char *fname = "mloutputimpl<Parent, Type>::writev()";
            Trace T(fname);
#endif
            //cout << typeid(*this).name();
            return 0;
         }

         int
         write()
         {
#ifdef DEBUG
            char *fname = "mloutputimpl<Parent, Type>::write()";
            Trace T(fname);
#endif
            //cout << typeid(*this).name();
            return 0;
         }
   };
   ///////////////////////////////////////////////////////////////
   ///////////////////////////////////////////////////////////////
   // --END MLSTREAMIMPL--
   ///////////////////////////////////////////////////////////////

#include "mlstreamimpl.tcc"

} // End namespace mls

#endif

