package day05;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;

public class PrintQueue {
    public void parse(InputStream in) throws IOException {
        new BufferedReader(new InputStreamReader(in)).lines()
            .toList();
    }
}
