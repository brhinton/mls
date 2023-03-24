///////////////////////////////////////////////////////////////
//  SPDX-License-Identifier: GPL-2.0-only
//
//  MLStreams
//  Copyright (c) 2001-2023, Bryan Hinton
//  All rights reserved.
//
//  mlsockbuf.cpp
//  Created by Bryan R. Hinton, on Tue Jun 26 2001, 21:51:36 CDT
//
//  File Contents: Implementation of the mlsockbuf component.
//  Please see mlsockbuf.h for full documentation of this system.
//
///////////////////////////////////////////////////////////////

#include "mlsockbuf.h"


namespace mls
{

   //BEGIN MLSOCKBUF
   mlsockbuf::mlsockbuf(int infd, int outfd) : mlpipebuf(infd, outfd)
   {
#ifdef DEBUG
      char *fname = "mlsockbuf::mlsockbuf(int infd, outfd)";
      Tracebuf T(fname);
      T.prdesc(m_in, m_out);
#endif

   }

   mlsockbuf::mlsockbuf(const mlsockbuf &copy)
   {
#ifdef DEBUG
      char *fname = "mlsockbuf::mlsockbuf(const mlsockbuf&copy)";
      Tracebuf T(fname);
#endif

   }

   mlsockbuf::~mlsockbuf()
   {
#ifdef DEBUG
      char *fname = "mlsockbuf::~mlsockbuf()";
      Tracebuf T(fname);
#endif

      if(m_out != -1 && ( (pptr() - pbase()) > 0) ) {
         sync();
      }
   }

   const mlsockbuf&
   mlsockbuf::operator=(const mlsockbuf &rhs)
   {
#ifdef DEBUG
      char *fname = "mlsockbuf::operator=(const mlsockbuf &rhs)";
      Tracebuf T(fname);
#endif

   }

   void
   mlsockbuf::DumpDiagnostics() const
   {
#ifdef DEBUG
      char *fname = "mlsockbuf::DumpDiagnostics() const";
      Tracebuf T(fname);
#endif

   }

   mlsockbuf::streamsize
   mlsockbuf::xsputn(const char *s, streamsize n)
   {
#ifdef DEBUG
      char *fname = "mlsockbuf::xsputn(char *s, streamsize n)";
      Tracebuf T(fname);
#endif

      if(n < epptr() - pptr()) {
         memmove(pptr(), s, n * sizeof(char_type));
         pbump(n);
         return n;
      } else {
         for(mlsockbuf::streamsize i = 0; i < n; i++) {
            if((int(sputc(s[i]))) == (int(EOF)))
               return i;
         }
         return n;
      }
   }

   mlsockbuf::int_type
   mlsockbuf::overflow(int_type c)
   {
#ifdef DEBUG
      char *fname = "mlsockbuf::overflow(int_type c)";
      Tracebuf T(fname);
#endif

      if(buffer_out() < 0)
         return EOF;

      else {
         if(c != EOF)
            return sputc(c);
         else
            return c;
      }
   }

   int
   mlsockbuf::sync()
   {
#ifdef DEBUG
      char *fname = "mlsockbuf::sync()";
      Tracebuf T(fname);
#endif

      return buffer_out();
   }

   int
   mlsockbuf::buffer_out()
   {
#ifdef DEBUG
      char *fname = "mlsockbuf::buffer_out()";
      Tracebuf T(fname);
#endif

      int cnt = pptr() - pbase();
      int retval = buffer_to_device(m_outbuf, cnt);
      pbump(-cnt);

      return retval;
   }

   int
   mlsockbuf::buffer_to_device(const char *c, int n)
   {
#ifdef DEBUG
      char *fname = "mlsockbuf::buffer_to_device(int_type c)";
      Tracebuf T(fname);
#endif

      if(write(m_out, c, n) != n)
         return -1;
      else
         return 0;
   }


   mlsockbuf::int_type
   mlsockbuf::underflow()
   {
#ifdef DEBUG
      char *fname = "mlsockbuf::underflow()";
      Tracebuf T(fname);
#endif

      if(gptr() < egptr())
         return (int)(unsigned char)(*gptr());

      if(buffer_in() < 0)
         return (int)EOF;

      else
         return (int)(unsigned char)(*gptr());
   }

   mlsockbuf::int_type
   mlsockbuf::pbackfail(int_type c)
   {
#ifdef DEBUG
      char *fname = "mlsockbuf::pbackfail(c)";
      Tracebuf T(fname);
#endif

      if(gptr() != eback()) {
         gbump(-1);
         if(c != ((int)EOF))
            *(gptr()) = char(c);
         return c;
      } else
         return (int(EOF));

   }

   int
   mlsockbuf::buffer_in()
   {
#ifdef DEBUG
      char *fname = "mlsockbuf::buffer_in()";
      Tracebuf T(fname);
#endif

      streamsize numPutbacks;
      if((gptr() - eback()) < pbSize)
         numPutbacks = (gptr() - eback());
      else
         numPutbacks = pbSize;

      memmove(m_inbuf + (pbSize-numPutbacks) * sizeof(char),
              gptr() - numPutbacks * sizeof(char),
              numPutbacks * sizeof(char));

      int retval = buffer_from_device((m_inbuf + pbSize * sizeof(char)),
                                      s_bufsiz - pbSize);

      if(retval <= 0) {
         setg(0,0,0);
         return -1;
      } else {
         setg(m_inbuf + pbSize - numPutbacks,
              m_inbuf + pbSize, m_inbuf + pbSize + retval);
         return retval;
      }
   }

   int
   mlsockbuf::buffer_from_device(char *c, int n)
   {
#ifdef DEBUG
      char *fname = "mlsockbuf::buffer_from_device(char *c, int n)";
      Tracebuf T(fname);
#endif

      return read(m_in, c, n);
   }

   int mlsockbuf::ml_socket(int domain, int type, int protocol)
   {
      m_in = m_out = socket(domain, type, protocol);
      return m_in;
   }

   int
   mlsockbuf::ml_connect(const struct sockaddr *name, int namelen)
   {
      return connect(m_in, name, namelen);
   }

   ssize_t
   mlsockbuf::ml_send(const void *buffer, size_t length, int flags)
   {
	  return send(m_in, buffer, length, flags);
   }

   ssize_t 
   mlsockbuf::ml_sendto(const void *msg, size_t len, int flags, 
		                const struct sockaddr *to, int tolen)
   {
	   return sendto(m_in, msg, len, flags, to, tolen);
   }

   ssize_t
   mlsockbuf::ml_sendmsg(const struct msghdr *msg, int flags)
   {
	   return sendmsg(m_in, msg, flags);
   }

} // End namespace mls
