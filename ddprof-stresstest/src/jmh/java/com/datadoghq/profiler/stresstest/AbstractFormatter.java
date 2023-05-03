package com.datadoghq.profiler.stresstest;

import java.io.IOException;
import java.io.PrintStream;
import java.nio.file.Files;
import java.nio.file.Path;

public abstract class AbstractFormatter implements Formatter {
    protected final PrintStream out;

    AbstractFormatter(Path file) throws IOException {
        Files.deleteIfExists(file);
        Files.createFile(file);
        this.out = new PrintStream(file.toFile());
    }

    final public void format() {
        print();
    }

    abstract protected void print();
}
