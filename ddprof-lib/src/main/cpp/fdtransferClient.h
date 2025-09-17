#ifndef _FD_TRANSFER_CLIENT_H
// async-profiler fdtransferClient.h shim

class FdTransferClient {
  public:
    static inline bool hasPeer() {
        return false;
    }

    static inline int requestKallsymsFd() {
        return -1;
    }
};
#endif // _FD_TRANSFER_CLIENT_H
