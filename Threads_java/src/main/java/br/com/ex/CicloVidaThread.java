package br.com.ex;
public class CicloVidaThread {
    private final static Object lock = new Object();

    public static void main(String[] args) {
        // Criação da thread (New)
        Thread thread = new Thread(new MinhaTarefa(lock));

        synchronized(lock) {
            // Inicia a thread (Runnable)
            thread.start();
            try {
                Thread.sleep(1000);
            }
            catch (InterruptedException e) {
                e.printStackTrace();
            }
            thread.interrupt();

            try {
                Thread.sleep(5* 1000);
            }
            catch (InterruptedException e) {
                e.printStackTrace();
            }
        }

        System.out.println("Main mantendo thread em wait");
        try {
            Thread.sleep(5* 1000);
        }
        catch (InterruptedException e) {
            e.printStackTrace();
        }

        System.out.println("Main vai liberar thread de wait");

        synchronized(lock) {
            lock.notify();
        }

        System.out.println("Main Liberou thread de wait");

        try {
        // A thread principal aguarda a conclusão da thread cri thread.join();
        }
        catch (InterruptedException e) {
            System.out.println("Thread principal foi interrompida.");
        }
        System.out.println("A thread principal terminou.");
    }
}

class MinhaTarefa implements Runnable {
    Object lock;
    public MinhaTarefa(Object lock) {
        System.out.println("Thread sendo construida.");
        this.lock = lock;
    }

    @Override
    public void run() {
        System.out.println("Thread está na fase de execução.");
        try{
            System.out.println("Thread vai entrar em time wait (sleep).");
            Thread.sleep(20 * 1000); // a thread está na fase de Timed Waiting
        }
        catch (InterruptedException e) {
            System.out.println("Thread foi interrompida durante o sono.");
        }

        System.out.println("Thread vai entrar em bloqueio.");
        synchronized(lock) { // a thread está na fase de Blocking
            System.out.println("Saiu do bloqueio.");
        }

        System.out.println("Thread está em fase de wait.");
        try {
            synchronized(lock) {
                lock.wait();
            }
        }
        catch (InterruptedException e) {
            e.printStackTrace();
        }
        System.out.println("Thread saiu de wait.");
        System.out.println("Thread terminou sua execução e agora está na fase Terminated.");
    }
}