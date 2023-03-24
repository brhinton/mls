///////////////////////////////////////////////////////////////
//  SPDX-License-Identifier: GPL-2.0-only
//
//  MLStreams
//  Copyright (c) 2001-2023, Bryan Hinton
//  All rights reserved.
//
//  MTException.h
//  Created by Bryan R. Hinton, on Mon Jul 02 2001, 17:35:31 CDT
//
//  File Contents: Interface and documentation of the MTException component.
//
///////////////////////////////////////////////////////////////

#ifndef MTLIBMTEXCEPTION_H
#define MTLIBMTEXCEPTION_H

#include <cstring>

// linkage specifications: functions listed here will not be name encoded.
extern "C"
{}

namespace MTLib
{

   /** Purpose: TODO: Describe the purpose of the class.
    *  (Everything that you write here will show up in the
    *  doc++ generated documentation.)
    */

   // exception class to map error codes from return values of
   // pthreads functions to messages.
   // upon throwing an exception of type ThrStartException,
   // an integer that represents the error code number returned
   // from pthread_create is passed to the constructor and stored.
   // a try catch block in turn calls the member function what()
   // which in turn calls strerror(ecode), where ecode is the
   // stored error code.  strerror maps this error number via errno.h
   // to a null terminated string. what subsequently returns this mesg
   // string that describes the error that occured.
   class MTException
   {

      public:
         /// Constructor
         // arg =  error code number
         MTException(int) throw();

         MTException(int, const char*) throw();

         MTException(const char*) throw();

         MTException(const MTException&) throw();

         const MTException&
         operator=(const MTException&) throw();

         virtual
         ~MTException() throw()
         { }

         int
         err(void) const throw()
         {
            return ecode;
         }

         const char*
         errmsg(void) const throw()
         {
            return strerror(ecode);
         }

         virtual const char*
         what() const throw()
         {
            return msg;
         }

      private:
         static const int MSGBUFSIZE = 80;
         int ecode;  // error code corresponding to errno val returned from pthreads function
         char msg[MSGBUFSIZE+1]; // optional error message

         MTException() throw()
         { }

#if 0

         static char const * const msg[] =
            { "The system lacked the necessary resources to \
              create another thread, or the system-imposed  \
              limit on the total number of threads in a process \
              PTHREAD_THREADS_MAX was exceeded. ",
              "The value specified by attr is invalid. ",
              "Caller does not have appropriate permission to set \
              the required scheduling parameters or schedulig policy."
         };
#endif

   };

} // End namespace MTLib

#endif
