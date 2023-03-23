///////////////////////////////////////////////////////////////
//
//  $Id: cstream.h,v 1.2 2002/05/18 21:26:23 alliz Exp $
//
//  MLStreams
//  Copyright (c) 2001-2002, Bryan Hinton
//  All rights reserved.
//
//  cstream.h
//  Created by Bryan R. Hinton, on Wed Jul 04 2001, 20:18:15 CDT
//
//  Copyright (C) 2001
//
//  File Contents: Interface and documentation of the cstream component.
//
///////////////////////////////////////////////////////////////

#ifndef MLSCSTREAM_H
#define MLSCSTREAM_H



// linkage specifications: functions listed here will not be name encoded.
extern "C"
{}

namespace mls
{

   /** Purpose: TODO: Describe the purpose of the class.
    *  (Everything that you write here will show up in the
    *  doc++ generated documentation.)
    */
   class cstream
   {

      public:
         /// Constructor.
         cstream();

         // Copy Constructor.
         cstream(const cstream&);

         // Destructor.
         virtual ~cstream();

         // Overloaded Assignment Operator.
         const cstream&
         operator=(const cstream&);

         /// DumpDiagnostics() dumps the object's state to standard output.
         void
         DumpDiagnostics() const;

      protected:

      private:

   }
   ; // End class cstream

} // End namespace mls

#endif

