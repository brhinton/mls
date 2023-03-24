///////////////////////////////////////////////////////////////
//  SPDX-License-Identifier: GPL-2.0-only
//
//  MLStreams
//  Copyright (c) 2001-2023, Bryan Hinton
//  All rights reserved.
//
//  mlsockbuf.h
//  Created by Bryan R. Hinton, on Tue Jun 26 2001, 21:51:36 CDT
//
//  File Contents: Interface and documentation of the mlsockbuf component.
//
///////////////////////////////////////////////////////////////

#ifndef MLSMLSOCKBUF_H
#define MLSMLSOCKBUF_H


#include "mlpipebuf.h"

// linkage specifications: functions listed here will not be name encoded.
extern "C"
{}

namespace mls
{

   class mlsockbuf : public mlpipebuf
   {

      public:
         /// Constructor.
         explicit mlsockbuf(int infd = 0, int outfd = 1);

         // Destructor.
         virtual ~mlsockbuf();

         /// DumpDiagnostics() dumps the object's state to standard output.
         void DumpDiagnostics() const;

         virtual void v1()
         {
#ifdef DEBUG
            char *fname = "virtual void mlsockbuf::v1()";
            Tracebuf t(fname);
#endif

         }

         virtual int ofd()
         {
#ifdef DEBUG
            char *fname = "virtual int mlsockbuf::ofd()";
            Tracebuf t(fname);
#endif

            return m_out;
         }

         ///////////////////////////////////////////////////////////////
         //
         //				--socket interface--
         //
         ///////////////////////////////////////////////////////////////
         int
         ml_socket(int domain, int type, int protocol);

         int
         ml_connect(const struct sockaddr *name, int namelen);

		 // send can only be used when socket is in a connected state
         ssize_t
         ml_send(const void *buffer, size_t length, int flags);

		 ssize_t
		 ml_sendto(const void *msg, size_t len, int flags, 
				   const struct sockaddr *to, int tolen);

		 ssize_t
	     ml_sendmsg(const struct msghdr *msg, int flags);
         ///////////////////////////////////////////////////////////////

      protected:
         //streambuf protected interface
         // Output related methods
         virtual streamsize xsputn(const char *s, streamsize n);
         virtual int_type overflow(int_type c=EOF);
         virtual int sync();
         virtual int buffer_out();
         virtual int buffer_to_device(const char *c, int n);

         // Input related methods
         virtual int_type underflow();
         virtual int_type pbackfail(int_type c);
         virtual int buffer_in();
         virtual int buffer_from_device(char *c, int n);

      private:

         // Copy Constructor.
         mlsockbuf(const mlsockbuf&);

         // Overloaded Assignment Operator.
         const mlsockbuf& operator=(const mlsockbuf&);

   }; // End class mlsockbuf

} // End namespace mls

#endif

