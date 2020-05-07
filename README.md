# A simple chatroom demo based on linux socket

The project consists of server entry and client entry using Qt5 to build the ui. It currently supports text messages and small file transfer only. The I/O status of sockets is monitored with epoll and message forward is accelerated with thread pool.

## Prerequisites
* Qt5
* MySQL (5.7)
* Redis (optional)
* hiredis (optional)

## Usage
Some variables need to be adapted, such as mysql login info, server listened addr and port, etc.

* Create a mysql table with fields username and password

* Build
  
  Run the following command lines to build the executables
  ```sh
  cmake \
  -DBUILD_CLIENT=ON \    # client application to be built
  -DBUILD_SERVER=ON \    # server application to be built
  -DUSE_REDIS_CACHE=ON   # use redis to cache messages for offline users
  .
  
  make                   # build libraries and excutables
  ```

* Run

  1. Run the executable `bin/serverui` built as above and specify ip and port to listen to.
  2. Run the executable `bin/clientui`, input username and password and try to login. You can also sign up to create a new account. To specify the server ip address and port to connect to, run
     ```
     ./bin/clientui ${ipaddr_server} ${port_server}
     ```