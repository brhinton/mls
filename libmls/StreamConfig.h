///////////////////////////////////////////////////////////////
//
//  $Id: StreamConfig.h,v 1.3 2002/07/26 22:39:50 alliz Exp $
//
//  MLStreams
//  Copyright (c) 2001-2002, Bryan Hinton
//  All rights reserved.
//
//  StreamConfig.h
//  Created by Bryan R. Hinton, on Wed Jul 04 2001, 20:04:54 CDT
//
//  Copyright (C) 2001
//
//  File Contents: Interface and documentation of the StreamConfig component.
//
///////////////////////////////////////////////////////////////

#ifndef MLSSTREAMCONFIG_H
#define MLSSTREAMCONFIG_H

// linkage specifications: functions listed here will not be name encoded.
extern "C"
{}

#include "Meta.h"
#include "mlbuf.h"

namespace mls
{

   ///////////////////////////////////////////////////////////////
   // forward declarations
   template<class BufType, int direction, class BaseType=mlbuf>
   class mlstreamimpl;

   template<class Parent, class BaseType=mlbuf>
   class mloutputimpl;

   template<class Parent, class BaseType=mlbuf>
   class mlinputimpl;

   template<class BufType, int direction, class BaseType=BufType>
   struct StreamConfig;

   template<class BufType, int direction, class BaseType>
   struct StreamConfig
   {
      //CASE<1,char, CASE<2,short, CASE<DEFAULT,int > > > >::RET i;
      //If direction == 0, generate an mlistream configuration based on BufferType
      //else If, direction == 1, generate an mlostream configuration based on BufferType
      //else If, direciton == 10, generate an mliostream configuration based on BufferType
      //else generate an istream configuration based on BufferType
      //
      //(i.e. assume BufferType is an mlbuf and direction == 0.  CASE 0 is evaluated
      //and an impl object is generated as follows:
      //impl<mlbuf, mlinputimpl<mlbuf, mlstreamimpl<mlbuf, 0>>>
      //mlbuf is the concrete buffer type.  mlinputimpl is designated
      //as the parent of impl.  mlinputimpl is then configured with an mlbuf buffer, and
      //it's parent is configured as an mlstreamimpl<mlbuf, 0>.
      //the second parameter to mlstreamimpl is the direction argument.
      //the 3rd parameter of mlstreamimpl is a dummy parameter which is defaulted and not
      //specified here.  In the case that BufferType == mlbuf, the generic implementation
      //of mlstreamimpl is instantiated, and the 2nd argument to mlstreamimpl which we specified
      //here as "0" is thrown out.  This provides overload resolution so that when BufferType == mlpipebuf
      //an impl is configured for a pipestream, where an explicit instantiation of mlinputimpl for pipebuf
      //is generated as the parent of impl, and subsequently an explicit instantiation of
      //mlstreamimpl for an mlpipebuf is generated as the parent of mlinputimpl<mlpipebuf>.
      //Back to mlstreamimpl and the overloaded resolution: Assume the currently generated code to
      //this point is inside of mlstreamimpl<mlpipebuf>. in this case, we need to inherit the
      //generic mlinputimpl and subsequently the generic mlstreamimpl for a basic mlistream.
      //mlstreamimpl<mlpipebuf, direction> uses a generator like the one here to generate
      //a common base heirarchy for the pipestream implementation.  The mlstreamimpl<mlpipebuf>
      //uses overload resolution to derive from an "mlinputimpl<mlpipebuf, direction, dummyvar>"
      //and subsequently an mlstreamimpl<mlpipebuf, direction, dummyvar> using the direction
      //parameter specified here.
      //mlstreamimpl<mlpipebuf
      //explicitely specifies a dummy variable as the third parameter in the PipeConfig selector.
      //If it did not do this, mlstreamimpl<mlpipebuf, direction> would try to recursively derived
      //itself( i.e. compile time error ...something to the extent of ambiguous overload resolution )
      typedef typename SWITCH<(direction),
      CASE<0,mlinputimpl<mlstreamimpl<BufType, direction, BaseType>, BufType >,
      CASE<1,mloutputimpl<mlstreamimpl<BufType, direction, BaseType>, BufType >,
      CASE<10,mlinputimpl<mloutputimpl<mlstreamimpl<BufType, direction, BaseType>, BufType >, BufType >,
      CASE<DEFAULT,mlinputimpl<mlstreamimpl<BufType, 10, BaseType>, BufType > > > > > >::RET Base;
   };

} // End namespace mls

#endif

