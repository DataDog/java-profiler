package com.datadoghq.profiler.cpu;

import java.io.InputStream;
import java.io.OutputStream;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.concurrent.ThreadLocalRandom;

public class IOBoundCode {
    private static final class IdleClient extends Thread {
        private final String host;
        private final int port;

        public IdleClient(String host, int port) {
            this.host = host;
            this.port = port;
            setDaemon(true);
        }

        @Override
        public void run() {
            try {
                byte[] buf = new byte[4096];

                try (Socket s = new Socket(host, port)) {
                    InputStream in = s.getInputStream();
                    while (in.read(buf) >= 0) {
                        // keep reading
                    }
                    System.out.println(Thread.currentThread().getName() + " stopped");
                }
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
    }

    private static final class BusyClient extends Thread {
        private final String host;
        private final int port;

        public BusyClient(String host, int port) {
            this.host = host;
            this.port = port;
            setDaemon(true);
        }

        @Override
        public void run() {
            try {
                byte[] buf = new byte[4096];

                try (Socket s = new Socket(host, port)) {

                    InputStream in = s.getInputStream();
                    while (in.read(buf) >= 0) {
                        // keep reading
                    }
                    System.out.println(Thread.currentThread().getName() + " stopped");
                }
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
    }

    void run() throws Exception {
        try (ServerSocket s = new ServerSocket(0)) {
            String host = "localhost";
            int port = s.getLocalPort();
            new IdleClient(host, port).start();
            OutputStream idleClient = s.accept().getOutputStream();

            new BusyClient(host, port).start();
            OutputStream busyClient = s.accept().getOutputStream();

            byte[] buf = new byte[4096];
            ThreadLocalRandom.current().nextBytes(buf);

            long target = System.nanoTime() + 3_000_000_000L;
            for (int i = 0; ; i++) {
                if ((i % 10_000_000) == 0) {
                    idleClient.write(buf, 0, 1);
                } else {
                    busyClient.write(buf);
                }
                if (System.nanoTime() >= target) {
                    break;
                }
            }
        }
    }
}
