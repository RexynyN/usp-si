package br.usp.utils;

import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.List;
import java.util.Optional;
import java.util.stream.Collectors;
import java.util.stream.Stream;
import br.usp.utils.Logger;

/**
 * Classe para lidar com a leitura de arquivos
 */
public class ResourcesReader {
    private static final String BASE_PATH = "src/main/resources/";

    /**
     * Funcao para ler um arquivo ate o final
     * @param fileName o nome do arquivo a ser lido
     * @return O conteudo do arquivo
     */
    public Optional<String> readAll(String fileName) {
        try {
            return Optional.of(Files.readString(Paths.get(BASE_PATH + fileName)).replaceAll("\n", ""));
        } catch (IOException e) {
            Logger.logln("Erro na leitura do arquivo: " + fileName + "\n" + e.getMessage());
            return Optional.empty();
        }
    }

    /**
     * Funcao para ler as linhas de um arquivo
     * @param filename O nome do arquivo
     * @return Uma lista com as linhas de um arquivo
     */
    public List<String> readLines(String filename) {
        try {
            Stream<String> lines = Files.lines(Path.of(BASE_PATH + filename));
            return lines.collect(Collectors.toList());
        } catch (IOException e) {
            Logger.logln("Erro na leitura do arquivo: " + filename + "\n" + e.getMessage());
            return null; // If Something breaks, this is to blame
        }
    }

    /**
     * Funcao para ler todos os arquivos de um diretorio
     * @param folderName o nome da pasta
     * @return a stream de arquivos, ordenada por ordem alfabetica pelo nome do arquivos
     */
    public List<File> getFilesInFolder(String folderName) {
        try {
            Stream<Path> filePaths = Files.walk(Paths.get(BASE_PATH + folderName));

            return filePaths
                    .map(Path::toFile)
                    .filter(File::isFile)
                    .sorted((file, other) -> file.getName().compareToIgnoreCase(other.getName()))
                    .collect(Collectors.toList());

        } catch (IOException e) {
            Logger.logln("Erro na leitura da pasta: " + folderName + "\n" + e.getMessage());
            return null;
        }
    }
}
