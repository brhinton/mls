///////////////////////////////////////////////////////////////
//
//  $Id: mlpipebuf.cpp,v 1.3 2002/05/18 21:26:23 alliz Exp $
//
//  MLStreams
//  Copyright (c) 2001-2002, Bryan Hinton
//  All rights reserved.
//
//  mlpipebuf.cpp
//  Created by Bryan R. Hinton, on Tue Jun 26 2001, 21:50:47 CDT
//
//  Copyright (C) 2001
//
//  File Contents: Implementation of the mlpipebuf component.
//  Please see mlpipebuf.h for full documentation of this system.
//
///////////////////////////////////////////////////////////////

#include "mlpipebuf.h"


namespace mls
{

   ///////////////////////////////////////////////////////////////
   //BEGIN MLPIPEBUF
   mlpipebuf::mlpipebuf(int infd, int outfd) : mlbuf(infd, outfd)
   {
#ifdef DEBUG
      char *fname = "mlpipebuf::mlpipebuf(int infd, outfd)";
      Tracebuf T(fname);
      T.prdesc(m_in, m_out);
#endif

   }

   mlpipebuf::mlpipebuf(const mlpipebuf &copy)
   {
#ifdef DEBUG
      char *fname = "mlpipebuf::mlpipebuf(const mlpipebuf&copy)";
      Tracebuf T(fname);
#endif

   }

   mlpipebuf::~mlpipebuf()
   {
#ifdef DEBUG
      char *fname = "mlpipebuf::~mlpipebuf()";
      Tracebuf T(fname);
#endif

      if( (pptr() - pbase()) > 0) {
         sync();
      }
   }

   const mlpipebuf&
   mlpipebuf::operator=(const mlpipebuf &rhs)
   {
#ifdef DEBUG
      char *fname = "mlpipebuf::operator=(const mlpipebuf &rhs)";
      Tracebuf T(fname);
#endif

   }

   void
   mlpipebuf::DumpDiagnostics() const
   {
#ifdef DEBUG
      char *fname = "mlpipebuf::DumpDiagnostics() const";
      Tracebuf T(fname);
#endif

   }

   mlpipebuf::streamsize
   mlpipebuf::xsputn(const char *s, streamsize n)
   {
#ifdef DEBUG
      char *fname = "mlpipebuf::xsputn(char *s, streamsize n)";
      Tracebuf T(fname);
#endif

      if(n < epptr() - pptr()) {
         memmove(pptr(), s, n * sizeof(char_type));
         pbump(n);
         return n;
      } else {
         for(mlpipebuf::streamsize i = 0; i < n; i++) {
            if((int(sputc(s[i]))) == (int(EOF)))
               return i;
         }
         return n;
      }
   }

   mlpipebuf::int_type
   mlpipebuf::overflow(int_type c)
   {
#ifdef DEBUG
      char *fname = "mlpipebuf::overflow(int_type c)";
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
   mlpipebuf::sync()
   {
#ifdef DEBUG
      char *fname = "mlpipebuf::sync()";
      Tracebuf T(fname);
#endif

      return buffer_out();
   }

   int
   mlpipebuf::buffer_out()
   {
#ifdef DEBUG
      char *fname = "mlpipebuf::buffer_out()";
      Tracebuf T(fname);
#endif

      int cnt = pptr() - pbase();
      int retval = buffer_to_device(m_outbuf, cnt);
      pbump(-cnt);

      return retval;
   }

   int
   mlpipebuf::buffer_to_device(const char *c, int n)
   {
#ifdef DEBUG
      char *fname = "mlpipebuf::buffer_to_device(int_type c)";
      Tracebuf T(fname);
#endif

      if(write(m_out, c, n) != n)
         return -1;
      else
         return 0;
   }

   mlpipebuf::int_type
   mlpipebuf::underflow()
   {
#ifdef DEBUG
      char *fname = "mlpipebuf::underflow()";
      Tracebuf T(fname);
#endif

      if(gptr() < egptr())
         return (int)(unsigned char)(*gptr());

      if(buffer_in() < 0)
         return (int)EOF;

      else
         return (int)(unsigned char)(*gptr());
   }

   mlpipebuf::int_type
   mlpipebuf::pbackfail(int_type c)
   {
#ifdef DEBUG
      char *fname = "mlpipebuf::pbackfail(c)";
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
   mlpipebuf::buffer_in()
   {
#ifdef DEBUG
      char *fname = "mlpipebuf::buffer_in()";
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
   mlpipebuf::buffer_from_device(char *c, int n)
   {
#ifdef DEBUG
      char *fname = " mlpipebuf::buffer_from_device(char *c, int n)";
      Tracebuf T(fname);
#endif

      return read(m_in, c, n);
   }

   int
   // read some bytes terminated by a newline from a socket descriptor
   mlpipebuf::Read_line(char *buffer, int size)
   {

      // init tmp pointer to beginning of buffer
      char *read_ptr = buffer;

      bool done = false;

      // number of bytes left in the array
      // that we "can" read. (i.e. empty space left in the array )
      int bytes_toread = size;

      // number of bytes just read
      int n;

      // handle interrupted system calls, subdivided reads
      // and terminated client connections
      do {

         n = read(m_in, read_ptr, bytes_toread);

         // if we read > 0 bytes
         if(n > 0) {
            // if the last byte read is not a newline
            if((*(read_ptr + n-1) != '\n') ) {
               // place the read ptr at the byte
               // after the last byte we just read
               read_ptr = (read_ptr + n);
               // decrement number of empty spaces
               // left in the array
               bytes_toread -= n;
               // keep going
               done = false;
            } else // we are done. we read a newline
               done = true;
         } else if(n == 0) {
            return 0; // other end terminated connection
         }
         // n < 0, i.e. n == -1

         else {
            if(errno == EINTR) // interrupted system call
               done = false; // keep going
            else
               return -1; // error, errno != EINTR
         }

      } while(!done && bytes_toread > 0);

      return 1;

   }

   // Write "n" bytes to a descriptor.
   ssize_t
   mlpipebuf::Writen(const char *vptr, size_t n)
   {
      size_t		nleft;
      ssize_t		nwritten;
      const char	*ptr;

      // init ptr to beginning of array
      ptr = (const char *)vptr;

      // number of bytes left to write
      nleft = n;

      while (nleft > 0) {
         if ( (nwritten = write(m_in, ptr, nleft)) <= 0) {
            if (errno == EINTR) // interrupted system call
               nwritten = 0;		// call write() again
            else
               return(-1);			// error
         }

         nleft -= nwritten; // decrement number of bytes left to write
         ptr   += nwritten; // increment number of bytes written
      }
      return(n); // return number of bytes written
   }



} // End namespace mls
