#include <iostream>
#include <getopt.h>
#include "TcpServer.h"
#include "EventLoop.h"
#include "EventLoopThreadPool.h"
#include <cstring>
#include <ctype.h>

int main(int argc, char *argv[]) {
  int threadNum = 2;
  int port = 6666;
  std::string logPath = "./WebServer.log";

  // parse args
  int opt;
  const char *str = "t:l:p:";
  while ((opt = getopt(argc, argv, str)) != -1) {
    switch (opt) {
      case 't': {
        threadNum = atoi(optarg);
        break;
      }
      case 'l': {
        logPath = optarg;
        if (logPath.size() < 2 || optarg[0] != '/') {
          printf("logPath should start with \"/\"\n");
          abort();
        }
        break;
      }
      case 'p': {
        port = atoi(optarg);
        break;
      }
      default:
        break;
    }
  }
// STL库在多线程上应用
/*#ifndef _PTHREADS
  LOG << "_PTHREADS is not defined !";
#endif*/
  EventLoop mainLoop;
  TcpServer myHTTPServer(&mainLoop, threadNum, port);
  myHTTPServer.Start();
  mainLoop.Loop();
  return 0;
}


