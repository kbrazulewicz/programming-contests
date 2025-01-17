package day09;

import commons.IOUtils;

import java.io.IOException;
import java.io.InputStream;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.NavigableSet;
import java.util.TreeSet;
import java.util.function.Function;
import java.util.stream.Collectors;
import java.util.stream.IntStream;

public class DiskFragmenter {

    private final static int FREE_SPACE = Integer.MIN_VALUE;
    private final static int MAX_LENGTH = 9;

    private int[] diskMap;

    private static class Entry {
        enum TYPE {FILE, FREE_SPACE}
        public final TYPE type;
        public final int fileId;
        public int start;
        public int length;

        private Entry(TYPE type, int fileId, int start, int length) {
            this.type = type;
            this.fileId = fileId;
            this.start = start;
            this.length = length;
        }

        public static Entry file(int fileId, int start, int length) {
            return new Entry(TYPE.FILE, fileId, start, length);
        }

        public static Entry freeSpace(int start, int length) {
            return new Entry(TYPE.FREE_SPACE, 0, start, length);
        }
    }

    private long checksum(Entry entry) {
        if (entry.type == Entry.TYPE.FREE_SPACE) {
            return 0;
        } else {
            return entry.fileId * ((long) entry.start * entry.length + (long) (entry.length - 1) * entry.length / 2);
        }
    }

    private long checksum(List<Entry> entries) {
        return entries.stream()
            .filter(entry -> entry.type == Entry.TYPE.FILE)
            .mapToLong(this::checksum)
            .sum();
    }

    public void parse(InputStream in) throws IOException {
        diskMap = IOUtils.parseLineOfDigits(in);
    }

    private List<Entry> initializeDirectory() {
        final List<Entry> directory = new ArrayList<>();
        int start = 0;
        for (int i = 0; i < diskMap.length; i++) {
            if (i % 2 == 0) {
                directory.add(Entry.file(i / 2, start, diskMap[i]));
            } else {
                directory.add(Entry.freeSpace(start, diskMap[i]));
            }
            start += diskMap[i];
        }

        return directory;
    }

    public long task1() {
        final List<Entry> directory = initializeDirectory();

        int indexL = 0;
        int indexR = directory.size() - 1;

        while (indexL < indexR) {
            var entryL = directory.get(indexL++);
            if (entryL.type != Entry.TYPE.FREE_SPACE) continue;
            if (indexR < 0) continue;

            var entryR = directory.get(indexR--);
            while (entryR.type != Entry.TYPE.FILE && indexR >= 0) {
                entryR = directory.get(indexR--);
            }
            if (entryR.type != Entry.TYPE.FILE) continue;

            if (entryL.length > entryR.length) {
                directory.set(indexR + 1, Entry.freeSpace(entryR.start, entryR.length));
                directory.set(indexL - 1, Entry.file(entryR.fileId, entryL.start, entryR.length));
                directory.add(indexL - 1, Entry.freeSpace(entryL.start + entryR.length, entryL.length - entryR.length));
                indexL--;
            } else if (entryL.length < entryR.length) {
                directory.set(indexL - 1, Entry.file(entryR.fileId, entryL.start, entryL.length));
                directory.set(indexR + 1, Entry.freeSpace(entryR.start + entryR.length - entryL.length, entryL.length));
                directory.add(indexR + 1, Entry.file(entryR.fileId, entryR.start, entryR.length - entryL.length));
                indexR++;
            } else {
                directory.set(indexL - 1, Entry.file(entryR.fileId, entryL.start, entryL.length));
                directory.set(indexR + 1, Entry.freeSpace(entryR.start, entryR.length));
            }
        }

        return checksum(directory);
    }

    public long task2() {
        final List<Entry> directory = initializeDirectory();

        final Map<Integer, NavigableSet<Integer>> fileMap = IntStream.range(0, MAX_LENGTH + 1)
                .boxed()
                .collect(Collectors.toMap(Function.identity(), key -> new TreeSet<>()));

        for (int i = 0; i < diskMap.length; i += 2) {
            int fileLength = diskMap[i];
            for (int l = fileLength; l <= MAX_LENGTH; l++) {
                fileMap.get(l).add(i);
            }
        }

        int writer = 0;
        for (int i = 0; i < diskMap.length; i++) {
            if (i % 2 == 1) {
                // free space
                int freeSpaceLength = diskMap[i];

                var filesThatWillFitIn = fileMap.get(freeSpaceLength).tailSet(i, false);
                while (!filesThatWillFitIn.isEmpty()) {
                    var rightmostFileThatWillFitIn = filesThatWillFitIn.last();
                    var fileLength = diskMap[rightmostFileThatWillFitIn];

                    // copy file
                    // erase the original

                    // remove the file from the fileMap
                    for (int l = fileLength; l <= MAX_LENGTH; l++) {
                        fileMap.get(l).remove(rightmostFileThatWillFitIn);
                    }

                    freeSpaceLength -= fileLength;
                    filesThatWillFitIn = fileMap.get(freeSpaceLength).tailSet(i, false);
                }
            } else writer += diskMap[i];
        }

        final List<Integer> diskMapList = Arrays.stream(diskMap).boxed().collect(Collectors.toCollection(ArrayList::new));
        final Map<Integer, NavigableSet<Integer>> freeSpaceMap = new HashMap<>();

        for (int i = 1; i < diskMapList.size(); i += 2) {
            int freeSpaceLength = diskMapList.get(i);
            for (int freeSpace = 1; freeSpace <= freeSpaceLength; freeSpace++) {
                freeSpaceMap.computeIfAbsent(freeSpace, key -> new TreeSet<>()).add(i);
            }
        }

        return checksum(directory);
    }
}