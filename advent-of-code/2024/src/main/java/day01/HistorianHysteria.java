package day01;

import java.io.InputStream;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;
import java.util.Map;
import java.util.Scanner;
import java.util.function.Function;
import java.util.stream.Collectors;
import java.util.stream.Stream;

/**
 * <a href="https://adventofcode.com/2024/day/1">Advent of Code 2024, day 1</a>
 */
public class HistorianHysteria {

    final private List<Long> left = new ArrayList<>();
    final private List<Long> right = new ArrayList<>();

    public void parse(InputStream in) {
        final Scanner sc = new Scanner(in);

        left.clear();
        right.clear();

        while (sc.hasNextLine()) {
            left.add(sc.nextLong());
            right.add(sc.nextLong());
        }
    }

    public long totalDistance() {
        Stream<Long> sLeft = left.stream().sorted();
        Iterator<Long> iLeft = sLeft.iterator();
        Stream<Long> sRight = right.stream().sorted();

        return sRight.filter(x -> iLeft.hasNext())
                .mapToLong(r -> Math.abs(iLeft.next() - r))
                .sum();
    }

    public long similarityScore() {
        Map<Long, Long> rFrequency = right.stream().collect(Collectors.groupingBy(Function.identity(), Collectors.counting()));

        return left.stream().mapToLong(l -> l * rFrequency.getOrDefault(l, 0L)).sum();
    }
}
