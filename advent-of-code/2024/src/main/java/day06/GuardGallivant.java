package day06;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;

public class GuardGallivant {
    private final static char OBSTACLE = '#';
    private final static char GUARD = '^';
    private final static char VISITED = 'X';

    enum Orientation {
        N, E, S, W
    }

    private char[][] map;
    private int guardX;
    private int guardY;
    private Orientation guardOrientation = Orientation.N;

    private void printMap() {
        System.out.println();
        for (var row : map) {
            System.out.println(row);
        }
    }

    public void parse(InputStream in) throws IOException {
        try (var reader = new BufferedReader(new InputStreamReader(in))) {
            var lines = reader.lines().toList();
            int xMax = lines.get(0).length();
            int yMax = lines.size();

            map = new char[yMax][xMax];
            for (int y = 0; y < yMax; y++) {
                var line = lines.get(y);
                for (int x = 0; x < xMax; x++) {
                    map[y][x] = line.charAt(x);

                    if (GUARD == map[y][x]) {
                        guardX = x;
                        guardY = y;
                    }
                }
            }
        }
    }

    public int task1() {
        int maxX = map[0].length;
        int maxY = map.length;

        do {
            int x = guardX;
            int y = guardY;
            map[y][x] = VISITED;
            switch (guardOrientation) {
                case N -> y--;
                case E -> x++;
                case S -> y++;
                case W -> x--;
            }
            if (x >= 0 && x < maxX && y >= 0 && y < maxY && map[y][x] == OBSTACLE) {
                switch (guardOrientation) {
                    case N -> guardOrientation = Orientation.E;
                    case E -> guardOrientation = Orientation.S;
                    case S -> guardOrientation = Orientation.W;
                    case W -> guardOrientation = Orientation.N;
                }
            } else {
                guardX = x;
                guardY = y;
            }
        } while (guardX >= 0 && guardX < maxX && guardY >= 0 && guardY < maxY);

        int visited = 0;
        for (var row : map) {
            for (var c : row) {
                if (c == VISITED) visited++;
            }
        }

        return visited;
    }
}
