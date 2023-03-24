///////////////////////////////////////////////////////////////
//  SPDX-License-Identifier: GPL-2.0-only
//
//  MLStreams
//  Copyright (c) 2001-2023, Bryan Hinton
//  All rights reserved.
//
//  Meta.h
//  Created by Bryan R. Hinton, on Wed Jul 04 2001, 20:01:21 CDT
//
//  File Contents: Interface and documentation of the Meta component.
//
///////////////////////////////////////////////////////////////

#ifndef MLSMETA_H
#define MLSMETA_H

// linkage specifications: functions listed here will not be name encoded.
extern "C"
{ }

namespace mls
{
   //IF<(1+2>4), short, int>::RET i; //the type of i is int
   template<bool condition, class Then, class Else>
   struct IF
   {
      typedef Then RET;
   };

   //specialization for condition==false
   template<class Then, class Else>
   struct IF<false, Then, Else>
   {
      typedef Else RET;
   };

   // case list -----------------
   const int DEFAULT  = ~(~0u >> 1); //initialize with the smallest int
   const int nilValue = DEFAULT+1;

   struct NilCase
   {
      enum {tag = nilValue};
      typedef NilCase RET;
   };

   template <int tag_,class Type_,class Next_ = NilCase>
   struct CASE
   {
      enum {tag = tag_};
      typedef Type_ Type;
      typedef Next_ Next;
   };

   //SWITCH<(1+1-2),
   //CASE<1,char, CASE<2,short, CASE<DEFAULT,int > > > >::RET i;
   //the DEFAULT case is selected and thus the type of i is int
   template <int tag,class Case>
   class SWITCH
   {
         typedef typename Case::Next NextCase;
         enum { 	caseTag = Case::tag,
                 nextTag = NextCase::tag,
                 found   = (caseTag == tag ||
                            caseTag == DEFAULT)
           };

         typedef typename IF<(nextTag == nilValue),
         NilCase,
         SWITCH<tag,NextCase>
         >::RET NextSwitch;

      public:
         typedef typename IF<found,
         typename Case::Type,
         typename NextSwitch::RET>::RET RET;
   };

} // End namespace mls

#endif

