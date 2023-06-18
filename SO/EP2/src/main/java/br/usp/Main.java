package br.usp;

import br.usp.database.WordDatabase;
import br.usp.executor.ThreadExecutor;
import br.usp.lock.ReaderWriterLock;
import br.usp.lock.SimpleLock;
import br.usp.utils.ResourcesReader;
import br.usp.utils.Logger;

public class Main {
    private static final int NUM_ITERATIONS = 50;

    private final ResourcesReader reader;

    public Main(ResourcesReader reader) {
        this.reader = reader;
    }

    public void initReadersWriters() {
        Logger.logln("Starting readers-writers");

        for (int i = 0; i < 101; i++) {
            WordDatabase database = new WordDatabase(reader.readLines("bd.txt"));
            Logger.logln("Starting with readers: " + i);
            long total = 0;
            for (int j = 0; j < NUM_ITERATIONS; j++) {
                Logger.logln("Iteration number: " + j);
                long duration = runExecutor(database, i);
                total += duration;
            }
            Logger.logln("Average duration: " + (total/NUM_ITERATIONS) + "ms");
        }
    }

    private long runExecutor(WordDatabase database, int numReaders) {

        // decomentar a linha de baixo para rodar: reader writer lock
        // ThreadExecutor executor = new ThreadExecutor(database, numReaders, new ReaderWriterLock());

        // decomentar a linha de baixo para rodar: simple lock
        ThreadExecutor executor = new ThreadExecutor(database, numReaders, new SimpleLock());
        try {
            executor.init();

            long start = System.currentTimeMillis();
            executor.start();
            long end = System.currentTimeMillis();
            long duration = end - start;
            Logger.logln("Duration: " + duration + "ms");
            return duration;
        } catch (InterruptedException e) {
            Logger.logln(e.getMessage());
            return 0L;
        }
    }

    public static void main(String[] args) {
        Main main = new Main(new ResourcesReader());

        main.initReadersWriters();
    }
}
