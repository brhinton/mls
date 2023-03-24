///////////////////////////////////////////////////////////////
//  SPDX-License-Identifier: GPL-2.0-only
//
//  MLStreams
//  Copyright (c) 2001-2023, Bryan Hinton
//  All rights reserved.
//
//  mlshmbuf.h
//  Created by Bryan R. Hinton, on Tue Jun 26 2001, 21:51:13 CDT
//
//  File Contents: Interface and documentation of the mlshmbuf component.
//
///////////////////////////////////////////////////////////////

#ifndef MLSMLSHMBUF_H
#define MLSMLSHMBUF_H

#include "mlbuf.h"

// linkage specifications: functions listed here will not be name encoded.
extern "C"
{}

namespace mls
{

   /** Purpose: TODO: Describe the purpose of the class.
    *  (Everything that you write here will show up in the
    *  doc++ generated documentation.)
    */
   class mlshmbuf : public mlbuf
   {

      public:
         /// Constructor.
         explicit mlshmbuf(int infd = 0, int outfd = 1);

         // Destructor.
         virtual
         ~mlshmbuf();

         /// DumpDiagnostics() dumps the object's state to standard output.
         void
         DumpDiagnostics() const;

         virtual void
         attach(int fd)
         {
            shm_in = fd;
         }

         virtual void
         v1()
         {
#ifdef DEBUG
            char *fname = "virtual void mlshmbuf::v1()";
            Tracebuf t(fname);
#endif

         }

         virtual int
         ofd()
         {
#ifdef DEBUG
            char *fname = "virtual int mlshmbuf::ofd()";
            Tracebuf t(fname);
#endif

            return shm_out;
         }
         ///////////////////////////////////////////////////////////////
         //
         //				--shared memory interface--
         //
         ///////////////////////////////////////////////////////////////
         void*
         ml_mmap(void *addr, size_t len, int prot, int flags,
                 /*int fildes,*/ off_t off);
         int
         ml_munmap(void *addr, size_t len);
         int
         ml_msync(void *addr, size_t len, int flags);
         int
         ml_mlockall(int flags);
         int
         ml_munlockall(void);
         int
         ml_mlock(caddr_t addr, size_t len);
         int
         ml_munlock(caddr_t addr, size_t len);

         //posix -lrt realtime library
         int
         ml_shm_open(const char *name, int oflag, mode_t mode);
         int
         ml_shm_unlink(/*const char *name*/);
         int
         ml_ftruncate(/*int fildes,*/ off_t length);
         int
         ml_fstat(/*int fildes*/ struct stat *buf);

         //system V shared memory
         //#include <sys/shm.h>
         int
         ml_shmget(key_t key, size_t size, int shmflg);
         void *
         ml_shmat(/*int shmid,*/ const void *shmaddr, int shmflg);
         int
         ml_shmdt(const void *shmaddr);
         int
         ml_shmctl(/*int shmid,*/ int cmd, struct shmid_ds *buf);
         ///////////////////////////////////////////////////////////////

      protected:
         // Output related methods
         virtual streamsize
         xsputn(const char *s, streamsize n);
         virtual int_type
         overflow(int_type c=EOF);
         virtual int
         sync();
         virtual int
         buffer_out();
         virtual int
         buffer_to_device(const char *c, int n);

         // Input related methods
         virtual int_type
         underflow();
         virtual int_type
         pbackfail(int_type c);
         virtual int
         buffer_in();
         virtual int
         buffer_from_device(char *c, int n);

      private:
         const static int s_bufsiz = 1024;
         const static streamsize pbSize = 32;

         // these will be mapped memory segments allocated at class construction
         char shm_outbuf[s_bufsiz];
         int shm_out;

         char shm_inbuf[s_bufsiz];
         int shm_in;

         // Copy Constructor.
         mlshmbuf(const mlshmbuf&);

         // Overloaded Assignment Operator.
         const mlshmbuf&
         operator=(const mlshmbuf&);

   }
   ; // End class mlshmbuf

} // End namespace mls

#endif

