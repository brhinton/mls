///////////////////////////////////////////////////////////////
//
//  $Id: mlbuf.h,v 1.4 2002/05/31 21:22:55 alliz Exp $
//
//  MLStreams
//  Copyright (c) 2001-2002, Bryan Hinton
//  All rights reserved.
//
//  mlbuf.h
//  Created by Bryan R. Hinton, on Tue Jun 26 2001, 21:51:08 CDT
//
//  Copyright (C) 2001
//
//  File Contents: Interface and documentation of the mlbuf component.
//
///////////////////////////////////////////////////////////////

#ifndef MLSMLBUF_H
#define MLSMLBUF_H

#include <streambuf>
#include <string>
#include <cstring>

// linkage specifications: functions listed here will not be name encoded.
extern "C"
{
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/uio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stropts.h>
#include <stdio.h>
#include <utime.h>
}

#include "Trace.h"

namespace mls
{

   //  Base streambuf class derived from std::streambuf
   //
   //  Maintains two internal character buffers.
   //  These buffers are used to represent an external device
   //  to which input and output is done.  They are a window
   //  to the external device.  Each array is 
   //  represented as a sequence of characters and represent 
   //  either a source or sink of characters.
   //  Three pointers are maintained
   //  inside each of the two buffers.  The pointers are adjusted 
   //  as input and output take place.  The buffers help give the 
   //  appearance of an unlimited sequence of characters.
   //  1.  Beginning pointer - lowest current element in the array
   //  2.  Next pointer - next element that is available for reading/writing
   //  3.  End pointer - first element beyond last position in array
   //  
   //  setg is used to setup the get area( input sequence )
   //  setg(char_type *gbeg, char_type *gnext, char_type *gend);
   //  setp is used to setup the put area( output sequence )
   //  setp(char_type *pbeg, char_type *pend);
   //  
   //  put area functions
   //  ------------------
   //  char_type* pbase() const;   start of put area
   //  char_type* pptr() const;	position at which next char is to be put
   //  char_type* epptr() const;	position one past end of current put area
   //  void pbump(int n) const;    advances next pointer by n
   // 
   //  get area functions
   //  ------------------
   //  char_type* eback() const;   start of get area
   //  char_type* gptr() const;    position at which next character is
   //  				               to be fetched.
   //  char_type* egptr() const;   position one past end of current get area
   //  void gbump(int n);          advances next pointer by n

   //template<LockType=FastMutex>
   class mlbuf : public std::streambuf
   {

         //typedef charT char_type;
         //typedef typename char_traits<char>::int_type int_type;
         //typedef typename traits::pos_type pos_type;
         //typedef typename traits::off_type off_type;
         //typedef traits traits_type

      public:
         //not using traits so these are typedefs
         typedef char char_type;
         typedef int int_type;
         typedef int streamsize;

         // Constructor.
         /// oppose usage of mlbuf constructor as a conversion constructor
         /// by declaring explicit.  arguments are
         //  the input and output file descriptors
         //  associated with the external device to which
         //  input and output is performed.  this class
         //  buffers input and output to the devices
         //  that these file descriptors refer to
         explicit mlbuf(int infd = 0, int outfd = 1);

         // Destructor.
         virtual
         ~mlbuf();

         /// DumpDiagnostics() dumps the object's state to standard output.
         void
         DumpDiagnostics() const;
         //fix
         virtual void
         ml_attach(int fd)
         {
            m_in = m_out = fd;
         }

         // virtual Test function
         virtual void
         v1()
         {
#ifdef DEBUG
            char *fname = "virtual void mlbuf::v1()";
            Tracebuf t(fname);
#endif

         }

         // return output file descriptor
         virtual int
         ofd()
         {
#ifdef DEBUG
            char *fname = "virtual int mlbuf::ofd()";
            Tracebuf t(fname);
#endif

            return m_out;
         }

         //calls the sync function in the protected
         //interface of this class( returns sync() )
         int
         pubsync()
         {
#ifdef DEBUG
            char *fname = "int pubsync()";
            Tracebuf t(fname);
#endif

         }

         //if a read position is available
         //returns egptr() - gptr(), otherwise
         //returns showmanyc.  showmanyc is part of
         //the protected interface and returns the number
         //of available characters in the get area.
         streamsize
         in_avail()
         { }

         ///////////////////////////////////////////////////////////////
         //
         //		--public interface used by mlstream objects--
         //
         ///////////////////////////////////////////////////////////////
         ///////////////////////////////////////////////////////////////
         //shmbuf will override this
         //  O_RDONLY, O_WRONLY, O_RDWR
         //  O_APPEND, O_CREAT
         //  O_DSYNC, O_EXCL, O_LARGEFILE, O_NOCTTY, O_NONBLOCK,
         //  or O_NDELAY, O_RSYNC, O_SYNC, O_TRUNC

         int
         ml_open(const char *path, int oflag, mode_t mode );

         int
         ml_close(/*int fildes*/);
         // equiv to open(path, O_WRONLY | O_CREAT | O_TRUNC, mode)
         int
         ml_creat(const char *path, mode_t mode);

         // SEEK_SET  the pointer is set to offset bytes.
         // SEEK_CUR  the pointer is set to its current location plus offset.
         // SEEK_END  the pointer is set to the size of the file plus offset.
         off_t
         ml_lseek(/*int fildes,*/ off_t offset, int whence);

         ssize_t
         ml_read(/*int fildes,*/ void *buf, size_t nbyte);

         ssize_t
         ml_pread(/*int fildes,*/ void *buf, size_t nbyte,
                                  off_t offset);
         void
         ml_test()
         {
            cout << "in mlbuf.h" << endl;
         }

         ssize_t
         ml_readv(/*int fildes,*/ const struct iovec *iov,
                                  int iovcnt);
         ssize_t
         ml_write(/*int fildes,*/ const void *buf,
                                  size_t nbyte);
         ssize_t
         ml_pwrite(/*int fildes,*/ const void *buf,
                                   size_t nbyte, off_t offset);
         ssize_t
         ml_writev(/*int fildes,*/ const struct iovec *iov,
                                   int iovcnt);
         int
         ml_dup(/*int fildes*/);

         int
         ml_dup2(/*int fildes,*/ int fildes2);

         int
         ml_fcntl(/*int fildes,*/ int cmd, /* arg */ ...);
         int
         ml_ioctl(/*int fildes,*/ int request, /* arg */ ...);
         //---------------------------------

         void
         init_finfo(void);

         // filename(pathname)
         int
         ml_stat(struct stat *buf);

         // if the filename is a link, then
         // information is returned about the link
         int
         ml_lstat(struct stat *buf);

         // returns info about the open file descriptor
         // contained within this mlbuf class
         int
         ml_fstat(struct stat *buf);
         //---------------------------------


         int
         ml_access(/*const char *path,*/ int amode);

         mode_t
         ml_umask(mode_t cmask);
		 
         int
         ml_chmod(/*const char *path,*/ mode_t mode);

         int
         ml_fchmod(/*int fildes,*/ mode_t mode);

         int
         ml_chown(/*const char *path,*/ uid_t owner, gid_t group);

         int
         ml_lchown(/*const char *path,*/ uid_t owner, gid_t group);

         int
         ml_fchown(/*int fildes,*/ uid_t owner, gid_t group);

         int
         ml_truncate(/*const char *path,*/ off_t length);

         int
         ml_ftruncate(/*int fildes,*/ off_t length);

         //int link(const char *existing, const char *new);
         int
         ml_unlink(/*const char *path*/);

         int
         ml_remove(/*const char *path*/);
         //int rename(const char *old, const char *new);

         int
         ml_symlink(/*const char *name1,*/ const char *name2);

         int
         ml_readlink(/*const char *path,*/ char *buf, size_t bufsiz);

         int
         ml_utime(/*const char *path,*/ const struct utimbuf *times);

         void
         ml_sync(void);

         int
         ml_fsync(/*int fildes*/);
         ///////////////////////////////////////////////////////////////


         ///////////////////////////////////////////////////////////////
         //
         //				--protected streambuf interface--
         //
         ///////////////////////////////////////////////////////////////
         //protected mlbuf interface.  The public interface
         //of this class is inherited from streambuf.  these
         //publicly inherited member functions call the
         //overriden member functions defined in the protected
         //interface of this class.
      protected:
         //----------------------------------
         // Output related methods ( Put Area )
         //
         // This is an optimization method and is similar
         // to repeated calls to int putc(c)  It writes n
         // characters in the array s to the put area.
         // returns the number of written chars.
         // overriding this method is optional
         virtual streamsize
         xsputn(const char_type *s, streamsize n);

         //sputc() and sputn() call this method when there
         //is no room in the put area to place a character
         //overflow subsequently clears out the put area
         //by calling buffer_out which calls buffer_to_device
         //to write the put area to the external device.
         //after doing that it calls sputc to place the
         //character c in the internal put buffer area.
         virtual int_type
         overflow(int_type c=EOF);

         //synchronizes the put area with the external device.
         //if pbase() is not null, the characters between
         //the characters between the beginning pointer
         //and the next pointer are written to the external
         //device. sync calls buffer_out
         virtual int
         sync();

         //calculates the number of characters in the current
         //put area, calls buffer_to_device, and then
         //moves the next pointer in the put area back the
         //number of characters written by calling pbump(-n)
         virtual int
         buffer_out();

         //this function contains device specific
         //functionality for writing to the external device
         //i.e. posix write
         virtual int
         buffer_to_device(const char *c, int n);
         //----------------------------------

         //----------------------------------
         // Input related methods ( Get Area )
         //

         //returns the number of available characters
         //in the get area
         //virtual int
         //showmanyc();

         //places n characters from the get area buffer
         //into the array s. Same as multiple calls to bumpc
         //virtual streamsize xsgetn(char_type *s, streamsize n);
         //Called by sgetc, spbumpc, snextc, sgetn when
         //there are no more chars to retrieve in the get
         //area.  Calls buffer_in which calls buffer_from_device
         //to fill the get area.
         virtual int_type
         underflow();

         //sbumpc() returns uflow() if a read position is not
         //available in the get area. uflow is called if
         //no get area buffer exists. it basically calls
         //underflow and increments the next pointer in the
         //get buffer.
         virtual int_type
         uflow()
         {
            return underflow();
         }

         //putback. When an attempt is made to put back
         //a character into the get area, and the get pointer
         //is already at the beginning of the input sequence.
         //begin pointer is null,
         //gptr == eback(begin pointer == next pointer)
         virtual int_type
         pbackfail(int_type c=EOF);

         //performs 3 steps.
         //1. copies the remaining characters at the
         //   end of the input buffer, to the beginning
         //   of the input buffer.
         //2. Next, it calls buffer_from_device to fill
         //   the internal get buffer, starting at the first
         //   available position in the input buffer( after the
         //   characters that it moved in step 1.
         //3. Last, it adjusts the begin pointer to point
         //   to the beginning of the character array. It
         //   adjusts the next pointer to point to the first
         //   character read from the external device, and the end
         //   pointer to point to the last character read from the
         //   external device.  If buffer_from_device returns
         //   an error, then buffer_in() invalidates the
         //   get area by calling setg(0,0,0);
         virtual int
         buffer_in();

         //this function contains device specific
         //functionality for reading from the external device.
         //i.e. posix read
         virtual int
         buffer_from_device(char *c, int n);
         //----------------------------------

         //----------------------------------
         //This section contains the get and put areas,
         //the size of these buffers, the size of the putback
         //area, and the 2 file descriptors associated with
         //This is part of the protected interface so
         //that derived streambuffers do not need
         //to override these values and can reuse
         //the file descriptors and buffers for efficiency
         //size of get(input) buffer
         const static int s_bufsiz = 1024;

         //this specifies the beginning of
         //the putback area reserve space for
         //32 chars at the beginning of the get area
         const static streamsize pbSize = 32;

         //character output (sub)sequence
         //put area
         char m_outbuf[s_bufsiz];

         //output file descriptor
         int m_out;

         //character input (sub)sequence
         //get area
         char m_inbuf[s_bufsiz];

         //input file descriptor
         int m_in;

         ///////////////////////////////////////////////////////////////
         //file information obtained via stat
         ///////////////////////////////////////////////////////////////
         //absolute pathname
         char *pathname;

         //file access mode
         mode_t mode;

         // user id of owner
         uid_t uid;

         // group id of file's group
         gid_t gid;

         //size of file last time we checked
         off_t size;

         // number of links to file
         nlink_t nlinks;

         //id of device containing a directory entry for file
         dev_t devid;

         //inode number
         ino_t inum;

         //prefered IO block size
         long blksize;

         // number of 512 byte blocks allocated
         blkcnt_t blocks;

         //time of last access
         time_t tlaccess;

         //time of last data modification
         time_t tldmod;

         //time of last file status change
         time_t tlstatus;

         //////////////////////////////////////////////////////////////

         ///////////////////////////////////////////////////////////////
      private:
         // Copy Constructor. disabled
         mlbuf(const mlbuf&);

         // Overloaded Assignment Operator. disabled
         const mlbuf&
         operator=(const mlbuf&);

   }; // End class mlbuf

} // End namespace mls

#endif

