///////////////////////////////////////////////////////////////
//  SPDX-License-Identifier: GPL-2.0-only
//
//  MLStreams
//  Copyright (c) 2001-2023, Bryan Hinton
//  All rights reserved.
//
//  mlshmbuf.cpp
//  Created by Bryan R. Hinton, on Tue Jun 26 2001, 21:51:13 CDT
//
//  File Contents: Implementation of the mlshmbuf component.
//  Please see mlshmbuf.h for full documentation of this system.
//
///////////////////////////////////////////////////////////////

#include "mlshmbuf.h"


namespace mls
{


   ///////////////////////////////////////////////////////////////
   //BEGIN MLSHMBUF
   mlshmbuf::mlshmbuf(int infd, int outfd) : shm_in(infd), shm_out(outfd), mlbuf(-1, -1)
   {
#ifdef DEBUG
      char *fname = "mlshmbuf::mlshmbuf(int infd, outfd)";
      Tracebuf T(fname);
      T.prdesc(shm_in, shm_out);
#endif

      //if it's a shared memory segment, buffersize will not change.
      //shm_inbuf will be a mapped region in memory
      setg(shm_inbuf, shm_inbuf+s_bufsiz, shm_inbuf+s_bufsiz);
      //setg(m_inbuf+pbSize, m_inbuf+pbSize, m_inbuf+pbSize);

      setp(shm_outbuf, shm_outbuf + s_bufsiz);
   }

   mlshmbuf::mlshmbuf(const mlshmbuf &copy)
   {
#ifdef DEBUG
      char *fname = "mlshmbuf::mlshmbuf(const mlshm &copy)";
      Tracebuf T(fname);
#endif

   }

   mlshmbuf::~mlshmbuf()
   {
#ifdef DEBUG
      char *fname = "mlshmbuf::~mlshmbuf()";
      Tracebuf T(fname);
#endif

      if(m_out != -1 && ( (pptr() - pbase()) > 0) ) {
         sync();
      }
   }

   const mlshmbuf&
   mlshmbuf::operator=(const mlshmbuf &rhs)
   {
#ifdef DEBUG
      char *fname = "mlshmbuf::operator=(const mlshmbuf &rhs)";
      Tracebuf T(fname);
#endif

   }

   void
   mlshmbuf::DumpDiagnostics() const
   {
#ifdef DEBUG
      char *fname = "mlshmbuf::DumpDiagnostics() const";
      Tracebuf T(fname);
#endif

   }

   mlshmbuf::streamsize
   mlshmbuf::xsputn(const char *s, streamsize n)
   {
#ifdef DEBUG
      char *fname = "mlshmbuf::xsputn(char *s, streamsize n)";
      Tracebuf T(fname);
#endif

      if(n < epptr() - pptr()) {
         memmove(pptr(), s, n * sizeof(char_type));
         pbump(n);
         return n;
      } else {
         for(mlshmbuf::streamsize i = 0; i < n; i++) {
            if((int(sputc(s[i]))) == (int(EOF)))
               return i;
         }
         return n;
      }
   }

   mlshmbuf::int_type
   mlshmbuf::overflow(int_type c)
   {
#ifdef DEBUG
      char *fname = "mlshmbuf::overflow(int_type c)";
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
   mlshmbuf::sync()
   {
#ifdef DEBUG
      char *fname = "mlshmbuf::sync()";
      Tracebuf T(fname);
#endif

      return buffer_out();
   }

   int
   mlshmbuf::buffer_out()
   {
#ifdef DEBUG
      char *fname = "mlshmbuf::buffer_out()";
      Tracebuf T(fname);
#endif

      int cnt = pptr() - pbase();
      int retval = buffer_to_device(shm_outbuf, cnt);
      pbump(-cnt);

      return retval;
   }

   int
   mlshmbuf::buffer_to_device(const char *c, int n)
   {
#ifdef DEBUG
      char *fname = "mlshmbuf::buffer_to_device(int_type c)";
      Tracebuf T(fname);
#endif

      if(write(shm_out, c, n) != n)
         return -1;
      else
         return 0;
   }

   mlshmbuf::int_type
   mlshmbuf::underflow()
   {
#ifdef DEBUG
      char *fname = "mlshmbuf::underflow()";
      Tracebuf T(fname);
#endif

      if(gptr() < egptr())
         return (int)(unsigned char)(*gptr());

      if(buffer_in() < 0)
         return (int)EOF;

      else
         return (int)(unsigned char)(*gptr());
   }

   mlshmbuf::int_type
   mlshmbuf::pbackfail(int_type c)
   {
#ifdef DEBUG
      char *fname = "mlshmbuf::pbackfail(c)";
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
   mlshmbuf::buffer_in()
   {
#ifdef DEBUG
      char *fname = "mlshmbuf::buffer_in()";
      Tracebuf T(fname);
#endif

      streamsize numPutbacks;
      if((gptr() - eback()) < pbSize)
         numPutbacks = (gptr() - eback());
      else
         numPutbacks = pbSize;

      memmove(shm_inbuf + (pbSize-numPutbacks) * sizeof(char),
              gptr() - numPutbacks * sizeof(char),
              numPutbacks * sizeof(char));

      int retval = buffer_from_device((shm_inbuf + pbSize * sizeof(char)),
                                      s_bufsiz - pbSize);

      if(retval <= 0) {
         setg(0,0,0);
         return -1;
      } else {
         setg(shm_inbuf + pbSize - numPutbacks,
              shm_inbuf + pbSize, shm_inbuf + pbSize + retval);
         return retval;
      }
   }

   int
   mlshmbuf::buffer_from_device(char *c, int n)
   {
#ifdef DEBUG
      char *fname = "mlshmbuf::buffer_from_device(char *c, int n)";
      Tracebuf T(fname);
#endif

      return read(shm_in, c, n);
   }

   void* mlshmbuf::ml_mmap(void *addr, size_t len, int prot, int flags, /*int fildes,*/ off_t off)
   {}

   int mlshmbuf::ml_munmap(void *addr, size_t len)
   {
      return 0;
   }

   int mlshmbuf::ml_msync(void *addr, size_t len, int flags)
   {
      return 0;
   }

   int mlshmbuf::ml_mlockall(int flags)
   {
      return 0;
   }

   int mlshmbuf::ml_munlockall(void)
   {
      return 0;
   }

   int mlshmbuf::ml_mlock(caddr_t addr, size_t len)
   {
      return 0;
   }

   int mlshmbuf::ml_munlock(caddr_t addr, size_t len)
   {
      return 0;
   }

   //posix -lrt realtime library
   int mlshmbuf::ml_shm_open(const char *name, int oflag, mode_t mode)
   {
      return 0;
   }

   int mlshmbuf::ml_shm_unlink(/*const char *name*/)
   {
      return 0;
   }

   int mlshmbuf::ml_ftruncate(/*int fildes,*/ off_t length)
   {
      return 0;
   }

   int mlshmbuf::ml_fstat(/*int fildes*/ struct stat *buf)
   {
      return 0;
   }

   //system V shared memory
   //#include <sys/shm.h>
   int mlshmbuf::ml_shmget(key_t key, size_t size, int shmflg)
   {
      return 0;
   }

   void * mlshmbuf::ml_shmat(/*int shmid,*/ const void *shmaddr, int shmflg)
   {
      return 0;
   }

   int mlshmbuf::ml_shmdt(const void *shmaddr)
   {
      return 0;
   }

   int ml_shmctl(/*int shmid,*/ int cmd, struct shmid_ds *buf)
   {
      return 0;
   }



} // End namespace mls
