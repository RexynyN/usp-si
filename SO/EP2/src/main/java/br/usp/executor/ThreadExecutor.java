package br.usp.executor;

import br.usp.database.WordDatabase;
import br.usp.lock.Lock;
import br.usp.lock.ReaderWriterLock;
import br.usp.utils.Logger;

import java.util.Collections;
import java.util.LinkedList;
import java.util.List;

public class ThreadExecutor {
    private static final int NUM_THREADS = 100;

    private final List<Thread> threads;
    private final WordDatabase database;
    private final Lock lock;

    /**
     * Atributo que determina a quantidade de readers
     */
    private final int qtdReaders;

    public ThreadExecutor(WordDatabase database, int qtdReaders, Lock lock) {
        this.threads = new LinkedList<>();
        this.database = database;
        this.qtdReaders = qtdReaders;
        this.lock = lock;
    }

    public void init() throws InterruptedException {
        for (int i = 0; i < NUM_THREADS; i++) {
            if (i < qtdReaders) {
                addReader();
            } else {
                addWriter();
            }
        }
        Collections.shuffle(this.threads);
    }

    public void start() {
        for (Thread thread : this.threads) {
            thread.start();
        }

        try {
            for (Thread thread : this.threads) {
                thread.join();
            }
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }

    private void addReader() {
        this.threads.add(new Thread(() -> {
            try {
                lock.readLock();
                Logger.logln(Thread.currentThread().getName() + " is reading");
                for (int j = 0; j < 100; j++) {
                    database.read();
                }
                Thread.sleep(1, 0);
                Logger.logln(Thread.currentThread().getName() + " finished reading");
                lock.readUnlock();
            } catch (Exception e) {
                e.printStackTrace();
            }
        }));
    }

    private void addWriter() {
        this.threads.add(new Thread(() -> {
            try {
                lock.writeLock();
                Logger.logln(Thread.currentThread().getName() + " is writing");
                for (int j = 0; j < 100; j++) {
                    database.write();
                }
                Thread.sleep(1, 0);
                Logger.logln(Thread.currentThread().getName() + " finished writing");
                lock.writeUnlock();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }));
    }

}
