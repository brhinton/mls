///////////////////////////////////////////////////////////////
//
//  $Id: Trace.cpp,v 1.2 2002/05/18 21:26:23 alliz Exp $
//
//  MLStreams
//  Copyright (c) 2001-2002, Bryan Hinton
//  All rights reserved.
//
//  Trace.cpp
//  Created by Bryan R. Hinton, on Sun Jun 17 2001, 22:02:04 CDT
//
//  Copyright (C) 2001
//
//  File Contents: Implementation of the Trace component.
//  Please see Trace.h for full documentation of this system.
//
///////////////////////////////////////////////////////////////

#include "Trace.h"


namespace mls
{

   bool Trace::isactive = false;

   /*Trace::Trace()
       {
       
       }
    
       Trace::Trace(const Trace &copy)
       {
    
       }
    
       Trace::~Trace()
       {
       
       }
       
       const Trace&
       Trace::operator=(const Trace &rhs)
       {
    
       }
    
       void
       Trace::DumpDiagnostics() const
       {
           std::cout << std::endl << std::endl << 
           "Trace Diagnostics dump "<< std::endl << std::endl;
       }
   	*/

   bool Tracebuf::isactive = false;

   /*    Tracebuf::Tracebuf()
       {
       
       }
    
       Tracebuf::Tracebuf(const Tracebuf &copy)
       {
    
       }
    
       Tracebuf::~Tracebuf()
       {
       
       }
       
       const Tracebuf&
       Tracebuf::operator=(const Tracebuf &rhs)
       {
    
       }
    
       void
       Tracebuf::DumpDiagnostics() const
       {
           std::cout << std::endl << std::endl << 
           "Trace Diagnostics dump "<< std::endl << std::endl;
       }
   	*/
} // End namespace mls
