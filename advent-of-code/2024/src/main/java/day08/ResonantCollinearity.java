package day08;

import java.io.IOException;
import java.io.InputStream;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.List;
import java.util.Map;
import java.util.Set;
import java.util.stream.Stream;

/**
 * <a href="https://adventofcode.com/2024/day/8">Advent of Code 2024, day 8</a>
 */
public class ResonantCollinearity {
    private static char EMPTY = '.';

    private char[][] map;
    private int xMax;
    private int yMax;

    private record Position(int x, int y) {
        @Override
        public String toString() {
            return String.format("[%d,%d]", x, y);
        }
    }

    private Map<Character, List<Position>> antennas;

    public void parse(InputStream in) throws IOException {
        map = commons.IOUtils.parseCharMatrix(in);
        xMax = map.length;
        yMax = map[0].length;

        antennas = new HashMap<>();
        for (int y = 0; y < yMax; y++) {
            for (int x = 0; x < xMax; x++) {
                if (map[x][y] != EMPTY) {
                    antennas.computeIfAbsent(map[x][y], c -> new ArrayList<>())
                            .add(new Position(x ,y));
                }
            }
        }
    }

    public void printAntennas() {
        for (var entry : antennas.entrySet()) {
            System.out.printf("[%c]:", entry.getKey());
            for (var position: entry.getValue()) {

                System.out.print(position);
            }
            System.out.println();
        }
    }

    private boolean withinMap(Position p) {
        return p.x >= 0 && p.x < xMax && p.y >= 0 && p.y < yMax;
    }

    public long task1() {
        final Set<Position> antinodes = new HashSet<>();
        for (var list : antennas.values()) {
            for (int a = 0; a < list.size(); a++) {
                var aPosition = list.get(a);
                for (int b = a + 1; b < list.size(); b++) {
                    var bPosition = list.get(b);

                    int dx = bPosition.x - aPosition.x;
                    int dy = bPosition.y - aPosition.y;

                    Stream.of(new Position(aPosition.x - dx, aPosition.y - dy),
                              new Position(bPosition.x + dx, bPosition.y + dy))
                            .filter(this::withinMap)
                            .forEach(antinodes::add);
                }
            }
        }

        return antinodes.size();
    }

    public long task2() {
        final Set<Position> antinodes = new HashSet<>();
        for (var list : antennas.values()) {
            for (int a = 0; a < list.size(); a++) {
                var aPosition = list.get(a);
                for (int b = a + 1; b < list.size(); b++) {
                    var bPosition = list.get(b);

                    int dx = bPosition.x - aPosition.x;
                    int dy = bPosition.y - aPosition.y;

                    Position antinode = aPosition;
                    while (withinMap(antinode)) {
                        antinodes.add(antinode);
                        antinode = new Position(antinode.x - dx, antinode.y - dy);
                    }
                    antinode = bPosition;
                    while (withinMap(antinode)) {
                        antinodes.add(antinode);
                        antinode = new Position(antinode.x + dx, antinode.y + dy);
                    }
                }
            }
        }

        return antinodes.size();
    }
}
