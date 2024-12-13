package day05;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.sql.Array;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.List;
import java.util.Map;
import java.util.Scanner;
import java.util.Set;
import java.util.function.Function;
import java.util.function.Predicate;
import java.util.stream.Collectors;

/**
 * <a href="https://adventofcode.com/2024/day/5">Print Queue</a>
 * Input is a rectangle.
 */
public class PrintQueue {

    private record OrderingRule(int x, int y) {}

    private List<OrderingRule> orderingRules = new ArrayList<>();
    private List<List<Integer>> updates = new ArrayList<>();

    private boolean isOrdered(List<Integer> update) {
        final Map<Integer, Integer> positions  = new HashMap<>();
        for (int i = 0; i < update.size(); i++) {
            positions.put(update.get(i), i);
        }

        return orderingRules.stream()
                .filter(r -> positions.containsKey(r.x) && positions.containsKey(r.y))
                .allMatch(r -> positions.get(r.x) < positions.get(r.y));
    }

    private List<Integer> fixOrdering(List<Integer> update) {
        return update;
    }

    public void parse(InputStream in) throws IOException {
        try (var reader = new BufferedReader(new InputStreamReader(in))) {

            // ordering rules
            while (reader.ready()) {
                String line = reader.readLine();
                if (line.isEmpty()) break;

                final Scanner scanner = new Scanner(line).useDelimiter("\\|");
                var x = scanner.nextInt();
                var y = scanner.nextInt();

                orderingRules.add(new OrderingRule(x, y));
            }

            // updates
            while (reader.ready()) {
                final Scanner scanner = new Scanner(reader.readLine()).useDelimiter(",");
                final List<Integer> update = new ArrayList<>();
                while (scanner.hasNextInt()) {
                    update.add(scanner.nextInt());
                }
                updates.add(update);
            }
        }
    }

    public int task1() {
        return updates.stream()
                .filter(this::isOrdered)
                .mapToInt(u -> u.get((u.size() - 1) >> 1))
                .sum();
    }

    public int task2() {
        return updates.stream()
                .filter(Predicate.not(this::isOrdered))
                .map(this::fixOrdering)
                .mapToInt(u -> u.get((u.size() - 1) >> 1))
                .sum();
    }
}
