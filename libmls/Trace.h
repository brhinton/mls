///////////////////////////////////////////////////////////////
//  SPDX-License-Identifier: GPL-2.0-only
//
//  MLStreams
//  Copyright (c) 2001-2023, Bryan Hinton
//  All rights reserved.
//
//  Trace.h
//  Created by Bryan R. Hinton, on Sun Jun 17 2001, 22:02:04 CDT
//
//  File Contents: Interface and documentation of the Trace component.
//
///////////////////////////////////////////////////////////////

#ifndef MLSTRACE_H
#define MLSTRACE_H

#include <iostream>
#include <string>

// linkage specifications: functions listed here will not be name encoded.
extern "C"
{}

namespace mls
{

   using namespace std;

   //utility class used for debugging.
   //sends error messages to stdout
   // Client instantiates a Trace object and passes it a
   // function/method name. debugging turned on/off via static data member

   class Trace
   {

      public:

         // Constructor.
         // Minimize overhead of construction and destruction
         // using partial initialization.
         Trace(const char *name) : functionname(0)
         {
            if(isactive) {
               cout << endl << "Enter function " << name << endl;
               functionname = new std::string(name);
            }
         }

         void 
		 debug(const char *msg)
         {
            if(isactive) {
               cout << endl << msg << endl;
            }
         }

         // Copy Constructor.
         Trace(const Trace&)
         {  }

         // Destructor.
         virtual ~Trace()
         {
            if(isactive) {
               cout << "Exit function " << *functionname << endl;
               delete functionname;
            }
         }

         // Overloaded Assignment Operator.
         const Trace& 
	     operator=(const Trace&)
         { }

         /// DumpDiagnostics() dumps the object's state to standard output.
         void 
		 DumpDiagnostics() const
		 { }

         static bool isactive;

      protected:

      private:
         std::string *functionname;

   }; // End class Trace


   class Tracebuf
   {

      public:

         // Constructor.
         // Minimize overhead of construction and destruction
         // using partial initialization.
         Tracebuf(const char *name) : functionname(0)
         {
            if(isactive) {
               cout << endl << "Enter function " << name << endl;
               functionname = new std::string(name);
            }
         }

         void 
		 debug(const char *msg)
         {
            if(isactive) {
               cout << endl << msg << endl;
            }
         }

         void 
		 prdesc(int i, int j = -1)
         {
            if(isactive) {
               cout << endl << i;
               if(j != -1)
                  cout << " " << j;

               cout << endl;
            }
         }

         // Copy Constructor.
         Tracebuf(const Tracebuf&)
         { }

         // Destructor.
         virtual ~Tracebuf()
         {
            if(isactive) {
               cout << "Exit function " << *functionname << endl;
               delete functionname;
            }
         }

         // Overloaded Assignment Operator.
         const Tracebuf& 
		 operator=(const Tracebuf&)
         { }

         // DumpDiagnostics() dumps the object's state to standard output.
         void DumpDiagnostics() const
         { }

         static bool isactive;

      protected:

      private:
         std::string *functionname;

   }; // End class Tracebuf

} // End namespace mls

#endif
