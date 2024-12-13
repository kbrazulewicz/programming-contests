package day03;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.List;
import java.util.TreeMap;
import java.util.regex.MatchResult;
import java.util.regex.Matcher;
import java.util.regex.Pattern;
import java.util.stream.Collectors;

public class MullItOver {
    private static final Pattern mulPattern = Pattern.compile("mul\\((\\d{1,3}),(\\d{1,3})\\)");
    private static final Pattern doPattern = Pattern.compile("do\\(\\)");
    private static final Pattern dontPattern = Pattern.compile("don't\\(\\)");

    private String memory;
    private List<MatchResult> mulOperations;
    private TreeMap<Integer, Boolean> enabledZones;

    public void parse(InputStream in) throws IOException {
        memory = new BufferedReader(new InputStreamReader(in)).lines()
            .collect(Collectors.joining());

        mulOperations = mulPattern.matcher(memory)
            .results()
            .toList();

        enabledZones = new TreeMap<>();
        enabledZones.put(0, true);

        doPattern.matcher(memory)
            .results()
            .map(MatchResult::end)
            .forEach(i -> enabledZones.put(i, true));

        dontPattern.matcher(memory)
            .results()
            .map(MatchResult::end)
            .forEach(i -> enabledZones.put(i, false));
    }

    private long mul(MatchResult matchResult) {
        return Long.parseLong(matchResult.group(1)) * Long.parseLong(matchResult.group(2));
    }

    public long mullEverything() {
        return mulOperations.stream()
            .mapToLong(this::mul)
            .sum();
    }

    public long mullOnlyEnabled() {
        return mulOperations.stream()
            .filter(matchResult -> enabledZones.floorEntry(matchResult.start()).getValue())
            .mapToLong(this::mul)
            .sum();
    }
}
