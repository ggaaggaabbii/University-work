package pkg;

import java.util.Random;
import java.util.concurrent.*;

public class Main {
    private static long runPool(int threadCount) {
        RejectionHandler rejectionHandler = new RejectionHandler();
        ThreadFactory threadFactory = Executors.defaultThreadFactory();
        ThreadPoolExecutor executorPool = new ThreadPoolExecutor(8, 8, 8, TimeUnit.SECONDS, new ArrayBlockingQueue<>(8), threadFactory, rejectionHandler);

        int dimx = 840;
        int dimy = 840;
        int cellCount = dimx * dimy;

        Random r = new Random();
        int[][] mat1 = new int[dimy][dimx];
        int[][] mat2 = new int[dimy][dimx];
        int[][] matr = new int[dimy][dimx];

        for (int i = 0; i < dimy; i++) {
            for (int j = 0; j < dimx; j++) {
                mat1[i][j] = r.nextInt(5) + 1;
                mat2[i][j] = r.nextInt(5) + 1;
            }
        }

        if (threadCount < 1 || cellCount % threadCount != 0) {
            System.out.println("Cannot equally assign work to threads.");
            System.exit(1);
        }

        int cellsPerThread = cellCount / threadCount;
        int currentX = 0;
        int currentY = 0;

        long start = System.currentTimeMillis();

        for (int i = 0; i < threadCount; i++) {
            Runnable worker = new ProductWorker(mat1, mat2, matr, dimy, dimx, currentY, currentX, cellsPerThread);

            currentY += (currentX + cellsPerThread) / dimx;
            currentX = (currentX + cellsPerThread) % dimx;

            executorPool.execute(worker);
        }

        executorPool.shutdown();
        while (!executorPool.isTerminated()) ;
        long end = System.currentTimeMillis();

        return end - start;
    }

    private static long runFuture(int threadCount) {
        ExecutorService executor = Executors.newFixedThreadPool(8);

        int dimx = 840;
        int dimy = 840;
        int cellCount = dimx * dimy;

        Random r = new Random();
        int[][] mat1 = new int[dimy][dimx];
        int[][] mat2 = new int[dimy][dimx];
        int[][] matr = new int[dimy][dimx];

        for (int i = 0; i < dimy; i++) {
            for (int j = 0; j < dimx; j++) {
                mat1[i][j] = r.nextInt(5) + 1;
                mat2[i][j] = r.nextInt(5) + 1;
            }
        }

        if (threadCount < 1 || cellCount % threadCount != 0) {
            System.out.println("Cannot equally assign work to threads.");
            System.exit(1);
        }

        int cellsPerThread = cellCount / threadCount;
        int currentX = 0;
        int currentY = 0;

        long start = System.currentTimeMillis();

        for (int i = 0; i < threadCount; i++) {
            FutureTask<Void> worker = new FutureTask<>(new ProductWorker(mat1, mat2, matr, dimy, dimx, currentY, currentX, cellsPerThread));

            currentY += (currentX + cellsPerThread) / dimx;
            currentX = (currentX + cellsPerThread) % dimx;

            executor.submit(worker);
        }

        executor.shutdown();
        while (!executor.isTerminated()) ;
        long end = System.currentTimeMillis();

        return end - start;
    }

    public static void main(String[] args) {
        for (int t = 1; t <= 8; t++) {
            long sum = 0;
            long count = 0;

            for (int i = 0; i < 25; i++) {
                sum += runFuture(t);
                count++;
            }
            System.out.println("" + t + ": " + (sum / count));
        }
    }
}
