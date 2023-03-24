// SPDX-License-Identifier: GPL-2.0-only
// MLStreams
// Copyright (c) 2001-2023, Bryan Hinton
// All rights reserved.
//
// main.cpp

#include "libmls/mlstream.h"
#include <strings.h>


using namespace mls;

class MBuffer
{

      template<class streamtype>
      friend streamtype& operator>>(streamtype&, MBuffer&);

      template<class streamtype>
      friend streamtype& operator<<(streamtype&, const MBuffer&);

   private:
      template<class streamtype>
      streamtype& extract(streamtype&);

      template<class streamtype>
      streamtype& insert(streamtype&) const;

      static const int BLOCKSIZE = 8192;
      char buffer[BLOCKSIZE];
};

template<class streamtype>
streamtype &MBuffer::extract(streamtype &is)
{
   is >> buffer;
   return is;
}

template<class streamtype>
streamtype &MBuffer::insert(streamtype &os) const
{
   os << buffer << endl;
   return os;
}
template<class streamtype>
inline streamtype& operator>>(streamtype &is, MBuffer& mbuf)
{
   return mbuf.extract(is);
}

template<class streamtype>
inline streamtype& operator<<(streamtype &os, const MBuffer& mbuf)
{
   return mbuf.insert(os);
}
///////////////////////////////////////////////////////////////

int
main(int argc, char **argv)
{


   using namespace std;

   char buf[80];
   itxtstream instream(0);
   otxtstream outstream(1);
   instream.open("t1.txt", O_RDONLY, 0777);
   instream >> buf;
   cout << buf << endl;
   outstream.open("t1.txt", O_WRONLY, 0777);
   outstream << "HELLO" << endl;


   struct sockaddr_un servaddr;

   sockstream rst(0,1);
   rst.socket(AF_UNIX, SOCK_STREAM, 0);

   bzero(&servaddr, sizeof(servaddr));
   servaddr.sun_family = AF_UNIX;
   strcpy(servaddr.sun_path, "/tmp/unix.statpath");

   rst.connect( (struct sockaddr *)&servaddr, sizeof(servaddr));

   const char *msg = "HELLO GOODBYE\n";
   //rst << "HELLO BYE\n" << endl;
   //rst >> buf;
   rst.Writen(msg, strlen(msg));
   rst.Readline(buf, 80);
   strcat(buf, "\0");
   cout << buf << endl;

   return 0;

}
