package br.usp.database;

import br.usp.utils.RandomGenerator;

import java.util.List;

public class WordDatabase {
    private final List<String> words;

    public WordDatabase(List<String> words) {
        this.words = words;
    }

    public void read() {
        try {
            int random = RandomGenerator.random(words.size() - 1);
            String s = this.words.get(random);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public void write() {
        try {
            int random = RandomGenerator.random(words.size() - 1);
            this.words.set(random, "MODIFICADO");
            // FIXME: Remover as linhas abaixo depois que estiver funcionando tudo
            String s = this.words.get(random);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

}
