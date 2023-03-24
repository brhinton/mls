///////////////////////////////////////////////////////////////
//  SPDX-License-Identifier: GPL-2.0-only
//
//  MLStreams
//  Copyright (c) 2001-2023, Bryan Hinton
//  All rights reserved.
//
//  mlsockstreamimpl.h
//  Created by Bryan R. Hinton, on Wed Jul 04 2001, 20:09:28 CDT
//
//  File Contents: Interface and documentation of the mlsockstreamimpl component.
//
///////////////////////////////////////////////////////////////

#ifndef MLSMLSOCKSTREAMIMPL_H
#define MLSMLSOCKSTREAMIMPL_H



// linkage specifications: functions listed here will not be name encoded.
extern "C"
{}

#include "mlpipestreamimpl.h"
#include "mlsockbuf.h"


namespace mls
{

   template<class BufType, int direction>
   class mlstreamimpl<BufType, direction, mlsockbuf> : public StreamConfig<BufType, direction, mlpipebuf>::Base
   {

         typedef typename StreamConfig<BufType, direction, mlpipebuf>::Base Parent;

      public:
         mlstreamimpl() : Parent()
         {
#ifdef DEBUG
            char *fname = "mlstreamimpl<Impl, direction, Sock>() :";
            Trace T(fname);
#endif

         }

         mlstreamimpl(int infd, int outfd)
               : Parent(infd, outfd)
         {
#ifdef DEBUG
            char *fname = "mlstreamimpl<Impl, direction, Sock>(int infd, int outfd) : Parent(infd, outfd)";
            Trace T(fname);
#endif

         }

         ~mlstreamimpl()
         {
#ifdef DEBUG
            char *fname = "virtual ~mlstreamimpl<mlsockbuf>()";
            Trace T(fname);
#endif

         }

         int
         open()//(const char *path, int oflag, mode_t mode)
         {
#ifdef DEBUG
            char *fname="mlstreamimpl<mlsockbuf>::open(const char *path, int oflag, mode_t mode)";
            Trace T(fname);
#ifdef RTTIDEBUG
            //make sure the correct derived function is getting called
            t.debug( (typeid(*this).name()) );
#endif
				#endif

            return 0;
         }

         int
         close()
         {
#ifdef DEBUG
            char *fname="mlstreamimpl<mlsockbuf>::close()";
            //cout << typeid(*this).name();
            Trace t(fname);
#endif

            return 0;
         }

         //stat
         int
         stat()
         {
#ifdef DEBUG
            char *fname="mlstreamimpl<mlsockbuf>::stat()";
            //cout << typeid(*this).name();
            Trace t(fname);
#endif

            return 0;
         }

         int
         socket(int domain, int type, int protocol)
         {
            return buf.ml_socket(domain, type, protocol);
         }

         int
         connect(const struct sockaddr *name, int namelen)
         {
            return buf.ml_connect(name, namelen);
         }

		 ssize_t
		 send(const void *buffer, size_t length, int flags)
         {
			 return buf.ml_send(buffer, length, flags);
	     }

		 ssize_t
	     sendto(const void *msg, size_t len, int flags, 
				const struct sockaddr *to, int tolen)
		 {
			 return buf.ml_sendto(msg, len, flags, to, tolen);
	     }

		 ssize_t
	     sendmsg(const struct msghdr *msg, int flags)
		 {
			 return buf.ml_sendmsg(msg, flags);
	     }


         int
         Readline(char *buffer, int size)
         {
            return buf.Read_line(buffer, size);
         }

         int
         Writen(const char *vptr, size_t n)
         {
            return buf.Writen(vptr, n);
         }
   };

   template<class Parent>
   class mlinputimpl<Parent, mlsockbuf> : public Parent
   {
      public:
         mlinputimpl() : Parent()
         { }

         mlinputimpl(int infd, int outfd) : Parent(infd, outfd)
         {
#ifdef DEBUG
            char *fname = "mlinputimpl<Parent, Sock>(int infd, int outfd) : Parent(infd, outfd)";
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
            char *fname="mlistreamimpl<shmbuf>::readv()";
            //cout << typeid(*this).name();
            Trace t(fname);
#endif

            return 0;
         }

         int
         read()
         {
#ifdef DEBUG
            char *fname="mlistreamimpl<mlshmbuf>::read()";
            Trace t(fname);
#endif

            return 0;
         }
   };

   template<class Parent>
   class mloutputimpl<Parent, mlsockbuf> : public Parent
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

         int
         pwrite()
         {
            return 0;
         }

         int
         writev()
         {
            return 0;
         }

         int
         write()
         {
            return 0;
         }
   };

#include "mlsockstreamimpl.tcc"

} // End namespace mls

#endif

