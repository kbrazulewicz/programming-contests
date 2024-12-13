package day02;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.List;
import java.util.Optional;
import java.util.Scanner;

/**
 * <a href="https://adventofcode.com/2024/day/2">Advent of Code 2024, day 2</a>
 */
public class RedNosedReports {

    private static class Report {
        private final List<Long> levels;
        private final List<Long> diffs;

        private Report(List<Long> levels) {
            this.levels = List.copyOf(levels);
            final List<Long> d = new ArrayList<>();
            for (int i = 1; i < levels.size(); i++) {
                d.add(levels.get(i - 1) - levels.get(i));
            }
            diffs = List.copyOf(d);
        }

        private Optional<Integer> getFirstProblemPosition() {
            var signum = Math.signum(diffs.get(0));

            for (int i = 0; i < diffs.size(); i++) {
                var diff = diffs.get(i);
                if (Math.abs(diff) < 1 || Math.abs(diff) > 3 || signum != Math.signum(diff)) return Optional.of(i);
            }

            return Optional.empty();
        }
    }

    private List<Report> reports;

    private long numberOfSafeReports;
    private long numberOfSafeReportsWithProblemDampener;

    private boolean isSafeReport(Report report) {
        return report.getFirstProblemPosition().isEmpty();
    }

    private boolean isSafeReportWithProblemDampener(Report report) {
        var problemPosition = report.getFirstProblemPosition();
        if (problemPosition.isEmpty()) return true;

        // we remove problematic element
        {
            int skip = problemPosition.get() + 1;
            List<Long> filteredLevels = new ArrayList<>(report.levels);
            filteredLevels.remove(skip);
            var newReport = new Report(new ArrayList<>(filteredLevels));

            if (newReport.getFirstProblemPosition().isEmpty()) return true;
        }

        // or element before
        {
            int skip = problemPosition.get();
            List<Long> filteredLevels = new ArrayList<>(report.levels);
            filteredLevels.remove(skip);
            var newReport = new Report(new ArrayList<>(filteredLevels));

            if (newReport.getFirstProblemPosition().isEmpty()) return true;
        }

        // or before before
        {
            int skip = problemPosition.get() - 1;
            if (skip >= 0) {
                List<Long> filteredLevels = new ArrayList<>(report.levels);
                filteredLevels.remove(skip);
                var newReport = new Report(new ArrayList<>(filteredLevels));

                if (newReport.getFirstProblemPosition().isEmpty()) return true;
            }
        }

        return false;
    }

    private Report parseReport(String line) {
        final Scanner scanner = new Scanner(line);
        final List<Long> levels = new ArrayList<>();
        while (scanner.hasNextLong()) {
            levels.add(scanner.nextLong());
        }
        return new Report(levels);
    }

    public void parse(InputStream in) throws IOException {
        reports = new BufferedReader(new InputStreamReader(in)).lines()
            .map(this::parseReport)
            .toList();

        numberOfSafeReports = reports.stream()
            .filter(this::isSafeReport)
            .count();

        numberOfSafeReportsWithProblemDampener = reports.stream()
            .filter(this::isSafeReportWithProblemDampener)
            .count();
    }

    public long getNumberOfSafeReports() {
        return numberOfSafeReports;
    }

    public long getNumberOfSafeReportsWithProblemDampener() {
        return numberOfSafeReportsWithProblemDampener;
    }
}
