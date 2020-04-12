# A simple chatroom demo based on linux socket

The demo consists of server entry and client entry using Qt5 to build the ui. It currently 
supports text messages only. The i/o of sockets is monitored with epoll and message epoll is
accelerated with thread pool.

## Usage
* Build
  
  Run the following command lines to build the executables
  ```sh
  cmake .
  make
  ```

* Run

  1. Run the executable `serverui` built as above and specify ip and port to listen to.
  2. Run the executable `clientui`, specify user name and try to connect to server socket.