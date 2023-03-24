///////////////////////////////////////////////////////////////
//  SPDX-License-Identifier: GPL-2.0-only
//
//  MLStreams
//  Copyright (c) 2001-2023, Bryan Hinton
//  All rights reserved.
//
//  mlpipebuf.h
//  Created by Bryan R. Hinton, on Tue Jun 26 2001, 21:50:47 CDT
//
//  File Contents: Interface and documentation of the mlpipebuf component.
//
///////////////////////////////////////////////////////////////

#ifndef MLSMLPIPEBUF_H
#define MLSMLPIPEBUF_H

#include "mlbuf.h"


// linkage specifications: functions listed here will not be name encoded.
extern "C"
{}

namespace mls
{

   class mlpipebuf : public mlbuf
   {

      public:
         /// Constructor.
         explicit mlpipebuf(int infd = 0, int outfd = 1);

         // Destructor.
         virtual
         ~mlpipebuf();

         /// DumpDiagnostics() dumps the object's state to standard output.
         void
         DumpDiagnostics() const;

         virtual void
         v1()
         {
#ifdef DEBUG
            char *fname = "virtual void mlpipebuf::v1()";
            Tracebuf t(fname);
#endif

            char *fname = "virtual void mlpipebuf::v1()";
            cout << endl << endl << endl << fname << endl << endl << endl;
         }

         virtual int
         ofd()
         {
#ifdef DEBUG
            char *fname = "virtual int mlpipebuf::ofd()";
            Tracebuf t(fname);
#endif

            return m_out;
         }

         void
         ml_test()
         {
            cout << "in mlpipebuf" << endl;
         }
         ///////////////////////////////////////////////////////////////
         //
         //             --pipe interface--
         //
         ///////////////////////////////////////////////////////////////

         // read some bytes terminated by a newline from a socket descriptor
         int
         Read_line(char *buffer, int size);

         // Write "n" bytes to a descriptor.
         ssize_t
         Writen(const char *vptr, size_t n);

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
         //virtual int
         //ofd();// { return m_out; }

         //kernel pipe buffer size(PIPE_BUF)
         //a write of < pipesize will not be interleaved if multiple writers exist
         size_t pipesize;

      private:

         // Overloaded Assignment Operator.
         const mlpipebuf&
         operator=(const mlpipebuf&);

         // Copy Constructor.
         mlpipebuf(const mlpipebuf&);
   }
   ; // End class mlpipebuf

} // End namespace mls

#endif

