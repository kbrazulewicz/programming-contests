package day08;

import java.io.IOException;
import java.io.InputStream;

public class ResonantCollinearity {

    private char[][] map;

    public void parse(InputStream in) throws IOException {
        map = commons.IOUtils.parseCharMatrix(in);
    }

    public long task1() {
        return 0;
    }
}
