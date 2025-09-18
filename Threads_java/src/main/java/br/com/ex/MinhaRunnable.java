/**
 * Classe que implementa Runnable
 */
public class MinhaRunnable implements Runnable {
    private String nome;
    public MinhaRunnable(String nome) {
        this.nome = nome;
    }

    @Override
    public void run() {
        for (int i = 0; i < 5; i++) {
            System.out.println(nome + " está executando: " + i);
            try {
                Thread.sleep(1000);
            } catch (InterruptedException e) {
                System.out.println(nome + " foi interrompida.");
            }
        }
        System.out.println(nome + " terminou a execução.");
    }
}