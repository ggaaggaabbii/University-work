package pkg;

import java.util.concurrent.Callable;

public class ProductWorker implements Runnable, Callable<Void> {

    private final int dimx, dimy;
    private final int stepsToDo;
    private int[][] mat1, mat2, matr;
    private int currentX, currentY;

    public ProductWorker(int[][] mat1, int[][] mat2, int[][] matr, int dimy, int dimx, int currentY, int currentX, int stepsToDo) {
        this.mat1 = mat1;
        this.mat2 = mat2;
        this.matr = matr;
        this.dimx = dimx;
        this.dimy = dimy;
        this.currentX = currentX;
        this.currentY = currentY;
        this.stepsToDo = stepsToDo;
    }

    @Override
    public void run() {
        for (int i = 0; i < this.stepsToDo; i++) {
            int sum = 0;
            for ( int j = 0; j < this.dimx; j++ ) {
                sum += mat1[this.currentY][j] * mat2[j][this.currentX];
            }
            matr[this.currentY][this.currentX] = sum;

            this.currentX++;

            if (this.currentX == this.dimx) {
                this.currentX = 0;
                this.currentY++;
            }
        }
    }

    @Override
    public Void call() {
        run();
        return null;
    }
}
