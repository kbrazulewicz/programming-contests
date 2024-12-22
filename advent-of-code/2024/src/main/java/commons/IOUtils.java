package commons;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;

public class IOUtils {
    public static char[][] parseCharMatrix(InputStream in) throws IOException {
        try (var reader = new BufferedReader(new InputStreamReader(in))) {
            var lines = reader.lines().toList();
            int xMax = lines.get(0).length();
            int yMax = lines.size();

            var map = new char[xMax][yMax];
            for (int y = 0; y < yMax; y++) {
                var line = lines.get(y);
                for (int x = 0; x < xMax; x++) {
                    map[x][y] = line.charAt(x);
                }
            }

            return map;
        }
    }
}
