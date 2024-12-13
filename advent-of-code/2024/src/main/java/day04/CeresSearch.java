package day04;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.List;
import java.util.regex.Pattern;
import java.util.stream.Collector;
import java.util.stream.IntStream;
import java.util.stream.Stream;

/**
 * <a href="https://adventofcode.com/2024/day/4">Ceres Search</a>
 * Input is a rectangle.
 */
public class CeresSearch {

    private Pattern patternA = Pattern.compile("XMAS");
    private Pattern patternB = Pattern.compile("SAMX");
    private List<String> input;
    private int xMax;
    private int yMax;

    private Collector<Object, StringBuilder, String> stringBuilderStringCollector = Collector.of(
        StringBuilder::new,
        StringBuilder::append,
        StringBuilder::append,
        StringBuilder::toString);

    private String verticalString(int i) {
        return input.stream()
            .map(s -> s.charAt(i))
            .collect(stringBuilderStringCollector);
    }

    private String diagonalLeftString(int start) {
        int x = Math.min(start, xMax - 1);
        int y = start - x;
        int l = Math.min(x + 1, yMax - y);

        return IntStream.range(0, l)
            .mapToObj(i -> input.get(y + i).charAt(x - i))
            .collect(stringBuilderStringCollector);
    }

    private String diagonalRightString(int start) {
        int y = Math.max(yMax - 1 - start, 0);
        int x = Math.max(0, start - yMax + 1);
        int l = Math.min(xMax - x, yMax - y);

        return IntStream.range(0, l)
            .mapToObj(i -> input.get(y + i).charAt(x + i))
            .collect(stringBuilderStringCollector);
    }

    private char charAt(int x, int y) {
        return input.get(y).charAt(x);
    }

    private boolean masAt(int x, int y) {
        if (charAt(x, y) != 'A') return false;

        String s1 = Stream.of(charAt(x - 1, y - 1), 'A', charAt(x + 1, y + 1)).collect(stringBuilderStringCollector);
        String s2 = Stream.of(charAt(x - 1, y + 1), 'A', charAt(x + 1, y - 1)).collect(stringBuilderStringCollector);

        return ("MAS".equals(s1) || "SAM".equals(s1)) && ("MAS".equals(s2) || "SAM".equals(s2));
    }

    public void parse(InputStream in) throws IOException {
        input = new BufferedReader(new InputStreamReader(in)).lines()
            .toList();
        xMax = input.get(0).length();
        yMax = input.size();
    }

    public long xmasPuzzle() {
        Stream<String> allStreams = Stream.concat(
            Stream.concat(
                input.stream(),
                IntStream.range(0, xMax).mapToObj(this::verticalString)
            ),
            Stream.concat(
                IntStream.range(0, xMax + yMax - 1).mapToObj(this::diagonalLeftString),
                IntStream.range(0, xMax + yMax - 1).mapToObj(this::diagonalRightString)
            )
        );

        return allStreams.mapToLong(line -> patternA.matcher(line).results().count() + patternB.matcher(line).results().count())
            .sum();
    }

    public long masPuzzle() {
        int count = 0;
        for (int x = 1; x < xMax - 1; x++) {
            for (int y = 1; y < yMax - 1; y++) {
                if (masAt(x, y)) count++;
            }
        }
        return count;
    }
}
