///////////////////////////////////////////////////////////////
//
//  $Id: mlpipestreamimpl.h,v 1.3 2002/05/18 21:26:23 alliz Exp $
//
//  MLStreams
//  Copyright (c) 2001-2002, Bryan Hinton
//  All rights reserved.
//
//  mlpipestreamimpl.h
//  Created by Bryan R. Hinton, on Wed Jul 04 2001, 20:09:24 CDT
//
//  Copyright (C) 2001
//
//  File Contents: Interface and documentation of the mlpipestreamimpl component.
//
///////////////////////////////////////////////////////////////

#ifndef MLSMLPIPESTREAMIMPL_H
#define MLSMLPIPESTREAMIMPL_H



// linkage specifications: functions listed here will not be name encoded.
extern "C"
{}

#include "mlstreamimpl.h"
#include "mlpipebuf.h"

namespace mls
{

   /** Purpose: TODO: Describe the purpose of the class.
    *  (Everything that you write here will show up in the
    *  doc++ generated documentation.)
    */
   template<class BufType, int direction>
   class mlstreamimpl<BufType, direction, mlpipebuf> : public StreamConfig<BufType, direction, mlbuf>::Base
   {
         typedef typename StreamConfig<BufType, direction, mlbuf>::Base Parent;

      public:
         mlstreamimpl() : Parent()
         {
#ifdef DEBUG
            char *fname = "mlstreamimpl<Impl, Direction, Pipe>() : StreamConfig<Impl, direction, Text>()";
            Trace T(fname);
#endif

         }

         mlstreamimpl(int infd, int outfd)
               : Parent(infd, outfd)
         {
#ifdef DEBUG
            char *fname = "mlstreamimpl<Impl, Direction, Pipe>(int infd, int outfd): StreamConfig<Impl, direction, Text>(infd, outfd)";
            Trace T(fname);
#endif

         }

         ~mlstreamimpl()
         {
#ifdef DEBUG
            char *fname = "virtual ~mlstreamimpl<Impl, Direction, Pipe>()";
            Trace T(fname);
#endif

         }

         /*
         int open()//(const char *path, int oflag, mode_t mode) 
         {
         	char *fname="mlstreamimpl<mlpipebuf>::open(const char *path, int oflag, mode_t mode)";
         	Trace T(fname);

         	#ifdef DEBUG
         	char *fname="mlstreamimpl<mlpipebuf>::open(const char *path, int oflag, mode_t mode)";
         	Trace T(fname);
         	#ifdef RTTIDEBUG
         	//make sure the correct derived function is getting called
         	t.debug( (typeid(*this).name()) );
         	#endif
         	#endif
         	
         	return 0;
         }
         */

         int close()
         {
#ifdef DEBUG
            char *fname="mlstreamimpl<mlpipebuf>::close()";
            //cout << typeid(*this).name();
            Trace t(fname);
#endif

            return 0;
         }

         //stat
         int stat()
         {
#ifdef DEBUG
            char *fname="mlstreamimpl<mlpipebuf>::stat()";
            //cout << typeid(*this).name();
            Trace t(fname);
#endif

            return 0;
         }
   };

   template<class Parent>
   class mlinputimpl<Parent, mlpipebuf> : public Parent
   {
      public:
         mlinputimpl() : Parent()
         { }

         mlinputimpl(int infd, int outfd) : Parent(infd, outfd)
         {
#ifdef DEBUG
            char *fname = "mlinputimpl<Parent, Pipe>(int infd, int outfd) : Parent(infd, outfd)";
            Trace T(fname);
#endif

         }

         int pread()
         {
            buf.ml_test();
            return 0;
         }

         int readv()
         {
#ifdef DEBUG
            char *fname="mlistreamimpl<BufferType>::readv()";
            //cout << typeid(*this).name();
            Trace t(fname);
#endif

            return 0;
         }

         int read()
         {
#ifdef DEBUG
            char *fname="mlistreamimpl<BufferType>::read()";
            Trace t(fname);
#endif

            return 0;
         }
   };


   template<class Parent>
   class mloutputimpl<Parent, mlpipebuf> : public Parent
   {
      public:
         mloutputimpl() : Parent()
         {
#ifdef DEBUG
            char *fname = "mloutputimpl<Parent, Pipe>() : Parent()";
            Trace T(fname);
#endif

         }

         mloutputimpl(int infd, int outfd) : Parent(infd, outfd)
         {
#ifdef DEBUG
            char *fname = "mloutputimpl<Parent, Pipe>(int infd, int outfd) : Parent(infd, outfd)";
            Trace T(fname);
#endif

         }

         int pwrite()
         {
#ifdef DEBUG
            char *fname = "mloutputimpl<Parent, Pipe>()::pwrite()";
            Trace T(fname);
#endif

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

#include "mlpipestreamimpl.tcc"

} // End namespace mls

#endif

