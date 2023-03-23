///////////////////////////////////////////////////////////////
//
//  $Id: mlbuf.cpp,v 1.3 2002/05/18 21:26:23 alliz Exp $
//
//  MLStreams
//  Copyright (c) 2001-2002, Bryan Hinton
//  All rights reserved.
//
//  mlbuf.cpp
//  Created by Bryan R. Hinton, on Tue Jun 26 2001, 21:51:08 CDT
//
//  Copyright (C) 2001
//
//  File Contents: Implementation of the mlbuf component.
//  Please see mlbuf.h for full documentation of this system.
//
///////////////////////////////////////////////////////////////

#include "mlbuf.h"


namespace mls
{

   mlbuf::mlbuf(int infd, int outfd) : m_in(infd), m_out(outfd),
         pathname(0)

   {

#ifdef DEBUG
      char *fname = "mlbuf::mlbuf(int infd, outfd)";
      Tracebuf T(fname);
      T.prdesc(m_in, m_out);
#endif

      //if a derived mlbuf class wishes to use it's own
      //buffering scheme and own descriptors, then it
      //will pass -1 to it's base class constructor
      //(this constructor), in turn buffering will not be
      //setup here.  TODO: cross-link get and put areas.
      //

      if(infd >= 0)
         //setup the get area(input sequence). 0 size initially.
         //underflow will adjust when called
         setg(m_inbuf+pbSize, m_inbuf+pbSize, m_inbuf+pbSize);

      if(outfd >= 0)
         //setup the put area(output sequence)
         setp(m_outbuf, m_outbuf+s_bufsiz);
      /*
      if( (infd >= 0) && (outfd == -1) ) { 
      	//setup the get area(input sequence). 0 size initially. 
      	//underflow will adjust when called
      	setg(m_inbuf+pbSize, m_inbuf+pbSize, m_inbuf+pbSize);
      } 
      else if( (infd == -1) && (outfd > 0) ) { 
      	//setup the put area(output sequence)
      	setp(m_outbuf, m_outbuf+s_bufsiz);
       	} 
      else if( (infd >= 0) && (outfd >= 0) ) {
      		setp(m_outbuf, m_outbuf+s_bufsiz);
      		setg(m_inbuf+pbSize, m_inbuf+pbSize, m_inbuf+pbSize);
         }
      else
      	;
      	*/
      init_finfo();
   }

   //copy constructor. disabled for now.
   //copying and initialization of streambufs with other
   //streambufs is unclear.
   mlbuf::mlbuf(const mlbuf &copy)
   {
#ifdef DEBUG
      char *fname = "mlbuf::mlbuf(const mlbuf&copy)";
      Tracebuf T(fname);
#endif

   }

   //destructor
   mlbuf::~mlbuf()
   {
#ifdef DEBUG
      char *fname = "mlbuf::~mlbuf()";
      Tracebuf T(fname);
#endif
      //if buffering is setup in this class,
      //the output file descriptor is != -1 and
      //there are characters in the put area
      //(i.e. the next pointer - the begin pointer is
      //greater than 0
      if( (m_out != -1) && ( (pptr() - pbase()) > 0) ) {
         sync();
      }

      if(pathname)
         delete [] pathname;
   }

   //overloaded assignment operator.  disabled for now.
   //assigning streambufs is unclear.
   const mlbuf&
   mlbuf::operator=(const mlbuf &rhs)
   {
#ifdef DEBUG
      char *fname = "mlbuf::operator=(const mlbuf &rhs)";
      Tracebuf T(fname);
#endif

   }

   //dump the state of the internal data members of this class.
   void
   mlbuf::DumpDiagnostics() const
   {
#ifdef DEBUG
      char *fname = "mlbuf::DumpDiagnostics() const";
      Tracebuf T(fname);
#endif

   }

   mlbuf::streamsize
   mlbuf::xsputn(const char *s, streamsize n)
   {
#ifdef DEBUG
      char *fname = "mlbuf::xsputn(char *s, streamsize n)";
      Tracebuf T(fname);
#endif

      mlbuf::int_type ret(EOF);
      //if the number of characters passed in
      //will fit in the internal put area, they are
      //copied over directly into the put area starting
      //at the position of next pointer.
      //that is the end pointer of the put area minus  the
      //next pointer of the put area is greater than n
      if(n < epptr() - pptr()) {
         memmove(pptr(), s, n * sizeof(char_type));
         //move the next pointer of the put area
         //forward by n positions, b/c n chars were just placed
         //in the put area
         pbump(n);
         //return the number of chars written to the put area
         return n;
      }
      //if the number of chars passed in will not fit into
      //the internal put area, then these chars
      //will be passed into the put area one by one
      else {
         for(mlbuf::streamsize i = 0; i < n; i++) {

            //if sputc returns EOF which indicates
            //that overflow returned eof, as sputc
            //calls overflow, then return the number
            //of chars successfully written to the
            //put buffer.
            //
            //If the put area is not available,
            //sputc(s[i]) returns overflow(s[i]),
            //else, sputc places s[i] at the position
            //that the next pointer refers in the output
            //sequence, increments the next pointer
            //and then returns int(s[i])
            //
            //In this case,
            //write would have returned EOF.
            if( int_type(sputc(s[i])) == ret )
               return i;
         }
         //otherwise return the full n characters that were
         //written to the put area.
         return n;
      }
      /*
      mlbuf::streamsize i = 0;
      while(i < n)
      	if (sputc(s[i++]) return i;
      	*/
   }

   mlbuf::int_type
   mlbuf::overflow(int_type c)
   {
#ifdef DEBUG
      char *fname = "mlbuf::overflow(int_type c)";
      Tracebuf T(fname);
#endif

      int_type ret(EOF);
      //ret = static_cast<unsigned char>( *gptr() );
      //return ret;

      //buffer_out calls buffer_to_device,
      //if buffer_to_device returns < 0,
      //this indicates that write failed,
      //so return EOF
      if(buffer_out() < 0)
         return ret;

      //buffer_out succeeded, and the put area
      //was written to the external device
      //i.e. buffer_to_device returned 0
      else {
         //if the char passed in is not EOF
         //place it in the next position of the put buffer
         //by calling sputc(c)
         if(c != ret)//EOF)
            return sputc(c);
         else
            //the char is equal to EOF. just return it
            return ret;// c;
      }
   }

   int
   mlbuf::sync()
   {
#ifdef DEBUG
      char *fname = "mlbuf::sync()";
      Tracebuf T(fname);
#endif
      //call buffer_out to empty out the put area to
      //the external device
      return buffer_out();
   }

   int
   mlbuf::buffer_out()
   {
#ifdef DEBUG
      char *fname = "mlbuf::buffer_out()";
      Tracebuf T(fname);
#endif
      //cnt = next pointer - base pointer.
      //this is the number of chars in the put area
      //that buffer_to_device will write to the external device
      int cnt = pptr() - pbase();

      int ret = buffer_to_device(m_outbuf, cnt);
      //adjust the next pointer of the put area
      //back cnt chars, as buffer_to_device wrote
      //cnt number of chars from the put buffer to the
      //external device
      pbump(-cnt);

      //0 if buffer_to_device was successful,
      //-1 if buffer_to_device did not write n chars
      return ret;
   }

   int
   mlbuf::buffer_to_device(const char *c, int n)
   {
#ifdef DEBUG
      char *fname = "mlbuf::buffer_to_device(int_type c)";
      Tracebuf T(fname);
#endif
      //write n chars in the array c to the external device
      //associated with file descriptor m_out
      //if write returns less than n chars, return -1
      //indicating failure, else return 0 indicating success
      if(write(m_out, c, n) != n)
         return -1;
      else
         return 0;
   }



   //underflow is called by sgetc, sbumpc, snextc, and sgetn
   //when there are no more chars to retrieve from the get area
   mlbuf::int_type
   mlbuf::underflow()
   {
#ifdef DEBUG
      char *fname = "mlbuf::underflow()";
      Tracebuf T(fname);
#endif

      int_type ret(EOF);

      //if the next pointer of the get area is less
      //than the end pointer of the get area.
      //the character pointed to by the next pointer is returned
      if(gptr() < egptr()) {
         //was unsigned char
         ret = static_cast<char_type>( *gptr() );
         return ret;
      }
      //static_cast<unsigned char>( *gptr() );
      //return (int)(unsigned char)(*gptr());

      //otherwise, make chars available in the get area from
      //the external device
      //
      //buffer_in calls buffer_from_device which reads from
      //the external device in order to make more chars
      //available in the get area
      //if(buffer_in() < 0)
      //	;
      //return result;
      //return (int)EOF;
      //else {
      //return the first new character in the get area
      //that buffer_in() obtained via buffer_from_device
      //	result = static_cast<unsigned char>( *gptr() );
      //return (int)(unsigned char)(*gptr());
      //	}

      if(buffer_in() > 0)
         ret = static_cast<unsigned char>( *gptr() );
      return ret;
      //return result;
   }

   mlbuf::int_type
   mlbuf::pbackfail(int_type c)
   {
#ifdef DEBUG
      char *fname = "mlbuf::pbackfail(c)";
      Tracebuf T(fname);
#endif

      int_type ret(EOF);

      //if the next pointer is not equal to the begin
      //pointer, the last consumed char can be made available
      //from the get area.
      if(gptr() != eback()) {
         gbump(-1); //set the get pointer back 1
         if(c != ret)//((int)EOF))
            *(gptr()) = static_cast<mlbuf::char_type>(c);  //write the char to the position
         //that the get pointer refers to
         return c;  //return the char just putback
      } else
         return ret;//(int(EOF));  //return eof if next pter == begin ptr
      //( no where to put back the char )
   }

   int
   mlbuf::buffer_in()
   {
#ifdef DEBUG
      char *fname = "mlbuf::buffer_in()";
      Tracebuf T(fname);
#endif

      streamsize numPutbacks;
      //if the number of chars between the next pointer
      //and the begin pointer is less than the size of
      //the putback area, set the number of putback chars
      //= to the number of chars between the next pointer and the
      //begin pointer
      if((gptr() - eback()) < pbSize)
         numPutbacks = (gptr() - eback());
      else
         numPutbacks = pbSize; //else set numPutbacks to the
      //size of the putback area

      //move the existing characters that are at the end of
      //the get area to the beginning of the get area, in order
      //to make room for more chars.
      memmove(m_inbuf + (pbSize-numPutbacks) * sizeof(char),
              gptr() - numPutbacks * sizeof(char),
              numPutbacks * sizeof(char));


      //fill the get area up with more chars starting at
      //the first available position
      int retval = buffer_from_device((m_inbuf + pbSize * sizeof(char)),
                                      s_bufsiz - pbSize);

      //if read() failed, invalidate the get area and return -1
      if(retval <= 0) {
         setg(0,0,0);
         return -1;
      } else {
         //set the begin pointer of the get area to the
         //size of the putback area - the number of chars
         //actually available for putback
         //set the next pointer of the put area to the beginning
         //of the put area(i.e. the first available char after
         //the last char in the putback area. this is the first
         //available char just read from the external device.)
         //set the end of the get area to the number of chars
         //read from the device + the size of the putback area,
         //starting at position 0 of m_inbuf. this is the
         //last char read from the external device.
         setg(m_inbuf + pbSize - numPutbacks,
              m_inbuf + pbSize, m_inbuf + pbSize + retval);
         //return the number of new chars in the get area
         return retval;
      }
   }

   int
   mlbuf::buffer_from_device(char *c, int n)
   {
#ifdef DEBUG
      char *fname = "mlbuf::buffer_from_device(char *c int n)";
      Tracebuf T(fname);
#endif

      return read(m_in, c, n);
   }

   int
   mlbuf::ml_open(const char *path, int oflag, mode_t mode )
   {
      if(pathname)
         delete [] pathname;
      pathname = new char[strlen(path) + 1];
      strncpy(pathname, path, strlen(path)+1);

      int tmp_fd = open(path, oflag, mode);
      //fix
      m_in = m_out = tmp_fd;
      return tmp_fd;
   }

   int
   mlbuf::ml_close(/*int fildes*/)
   {
      //fix
      if(m_in != -1)
         close(m_in);
      if(m_out != -1)
         close(m_out);
   }

   // equiv to open(path, O_WRONLY | O_CREAT | O_TRUNC, mode)
   int
   mlbuf::ml_creat(const char *path, mode_t mode)
   {
      return 0;
   }

   // SEEK_SET  the pointer is set to offset bytes.
   // SEEK_CUR  the pointer is set to its current location plus offset.
   // SEEK_END  the pointer is set to the size of the file plus offset.
   off_t
   mlbuf::ml_lseek(/*int fildes,*/ off_t offset, int whence)
   {
      return 0;
   }

   ssize_t
   mlbuf::ml_read(/*int fildes,*/ void *buf, size_t nbyte)
   {
      return 0;
   }

   ssize_t
   mlbuf::ml_pread(/*int fildes,*/ void *buf, size_t nbyte,
                                   off_t offset)
   {
      return 0;
   }

   ssize_t
   mlbuf::ml_readv(/*int fildes,*/ const struct iovec *iov,
                                   int iovcnt)
   {
      return 0;
   }

   ssize_t
   mlbuf::ml_write(/*int fildes,*/ const void *buf,
                                   size_t nbyte)
   {
      return 0;
   }

   ssize_t
   mlbuf::ml_pwrite(/*int fildes,*/ const void *buf,
                                    size_t nbyte, off_t offset)
   {
      return 0;
   }

   ssize_t
   mlbuf::ml_writev(/*int fildes,*/ const struct iovec *iov, int iovcnt)
   {
      return 0;
   }

   int
   mlbuf::ml_dup(/*int fildes*/)
   {
      return 0;
   }

   int
   mlbuf::ml_dup2(/*int fildes,*/ int fildes2)
   {
      return 0;
   }


   int
   mlbuf::ml_fcntl(/*int fildes,*/ int cmd, /* arg */ ...)
   {
      return 0;
   }

   int
   mlbuf::ml_ioctl(/*int fildes,*/ int request, /* arg */ ...)
   {
      return 0;
   }


   void
   mlbuf::init_finfo(void)
   {
      struct stat stats;

      // stat file maintained by streambuf
      if(pathname)
         ml_stat(&stats);
      else
         ml_fstat(&stats);

      // copy over statistics into
      // corresponding data members
      mode = stats.st_mode;
      size = stats.st_size;
      devid = stats.st_dev;
      inum = stats.st_ino;
      blksize = stats.st_blksize;
      tlaccess = stats.st_atime;
      tldmod = stats.st_mtime;
      tlstatus = stats.st_ctime;
      uid = stats.st_uid;
      gid = stats.st_gid;
      nlinks = stats.st_nlink;
      blocks = stats.st_blocks;
   }






   int
   mlbuf::ml_stat(/*const char *path,*/ struct stat *buf)
   {
      return stat(pathname, buf);
   }

   int
   mlbuf::ml_lstat(/*const char *path*/ struct stat *buf)
   {
      return lstat(pathname, buf);
   }

   int
   mlbuf::ml_fstat(/*int fildes,*/ struct stat *buf)
   {
      // determine which file descriptor to fstat

      // if input file descriptor is > 0
      // then we are using it
      if(m_in > 0)
         return fstat(m_in, buf);

      // if output file descriptor is > 1
      // then we are using it
      if(m_out > 1)
         return fstat(m_out, buf);
   }

   int
   mlbuf::ml_access(/*const char *path,*/ int amode)
{}

   mode_t
   mlbuf::ml_umask(mode_t cmask)
   {
      return 0;
   }

   int
   mlbuf::ml_chmod(/*const char *path,*/ mode_t mode)
   {
      return 0;
   }

   int
   mlbuf::ml_fchmod(/*int fildes,*/ mode_t mode)
   {
      return 0;
   }

   int
   mlbuf::ml_chown(/*const char *path,*/ uid_t owner, gid_t group)
   {
      return 0;
   }

   int
   mlbuf::ml_lchown(/*const char *path,*/ uid_t owner, gid_t group)
   {
      return 0;
   }

   int
   mlbuf::ml_fchown(/*int fildes,*/ uid_t owner, gid_t group)
   {
      return 0;
   }

   int
   mlbuf::ml_truncate(/*const char *path,*/ off_t length)
   {
      return 0;
   }

   int
   mlbuf::ml_ftruncate(/*int fildes,*/ off_t length)
   {
      return 0;
   }

   //int link(const char *existing, const char *new);
   int
   mlbuf::ml_unlink(/*const char *path*/)
   {
      return 0;
   }

   int
   mlbuf::ml_remove(/*const char *path*/)
   {
      return 0;
   }

   //int rename(const char *old, const char *new);

   int
   mlbuf::ml_symlink(/*const char *name1,*/ const char *name2)
   {
      return 0;
   }

   int
   mlbuf::ml_readlink(/*const char *path,*/ char *buf, size_t bufsiz)
   {
      return 0;
   }

   int
   mlbuf::ml_utime(/*const char *path,*/ const struct utimbuf *times)
   {
      return 0;
   }

   void
   mlbuf::ml_sync(void)
   {}

   int
   mlbuf::ml_fsync(/*int fildes*/)
   {
      return 0;
   }



} // End namespace mls
