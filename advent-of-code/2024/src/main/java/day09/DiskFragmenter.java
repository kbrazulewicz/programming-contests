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

    private static class EntryX {
        enum TYPE {FILE, FREE_SPACE}
        public final TYPE type;
        public final int fileId;
        public int start;
        public int length;

        private EntryX (TYPE type, int fileId, int start, int length) {
            this.type = type;
            this.fileId = fileId;
            this.start = start;
            this.length = length;
        }

        public static EntryX file(int fileId, int start, int length) {
            return new EntryX(TYPE.FILE, fileId, start, length);
        }

        public static EntryX freeSpace(int start, int length) {
            return new EntryX(TYPE.FREE_SPACE, 0, start, length);
        }
    }

    private class Entry {
        public int entryId;
        public int offset;

        private Entry(int entryId, int offset) {
            this.entryId = entryId;
            this.offset = offset;
        }

        private boolean isFile() {
            return entryId % 2 == 0;
        }

        private void moveRight() {
            offset++;
            // skip everything of size 0
            while (offset >= diskMap[entryId]) {
                entryId++;
                offset = 0;
            }
        }

        private int entryIdAndMoveRight() {
            int currentEntryId = entryId;
            moveRight();
            return currentEntryId;
        }

        // skips free space
        private int entryIdAndMoveLeft() {
            int currentEntryId = entryId;
            offset--;
            if (offset < 0) {
                entryId -= 2;
                offset = diskMap[entryId] - 1;
            }

            return currentEntryId;
        }
    }

    private Entry leftReader() {
        return new Entry(0, 0);
    }

    private Entry rightReader() {
        int entryId = diskMap.length - 1;
        return new Entry(entryId, diskMap[entryId] - 1);
    }

    private int fragmenterNextBlock(Entry entryL, Entry entryR) {
        if (entryL.isFile()) {
            return entryL.entryIdAndMoveRight();
        } else {
            entryL.moveRight();
            return entryR.entryIdAndMoveLeft();
        }
    }

    private long totalFileBlocks() {
        long totalBlocks = 0;
        for (int i = 0; i < diskMap.length; i += 2) {
            totalBlocks += diskMap[i];
        }
        return totalBlocks;
    }

    private int[] fillBlocks() {
        int numberOfBlocks = Arrays.stream(diskMap).sum();
        var blocks = new int[numberOfBlocks];

        int writeIndex = 0;

        for (int i = 0; i < diskMap.length; i++) {
            if (i % 2 == 0) {
                // file
                for (int j = 0; j < diskMap[i]; j++) {
                    blocks[writeIndex++] = i / 2;
                }
            } else {
                // space
                for (int j = 0; j < diskMap[i]; j++) {
                    blocks[writeIndex++] = FREE_SPACE;
                }
            }
        }

        return blocks;
    }

    private long checksum(int[] blocks) {
        return checksum(blocks, blocks.length);
    }

    private long checksum(int[] blocks, int length) {
        long checksum = 0;
        for (int i = 0; i < length; i++) {
            if (blocks[i] != FREE_SPACE) {
                checksum += (long) i * blocks[i];
            }
        }

        return checksum;
    }

    private long checksumm(EntryX entry) {
        if (entry.type == EntryX.TYPE.FREE_SPACE) {
            return 0;
        } else {
            return entry.fileId * (entry.start + (long) (entry.length - 1) * entry.length / 2);
        }
    }

    private long checksum(List<EntryX> entries) {
        return entries.stream()
            .filter(entry -> entry.type == EntryX.TYPE.FILE)
            .mapToLong(this::checksumm)
            .sum();
    }

    public void parse(InputStream in) throws IOException {
        diskMap = IOUtils.parseLineOfDigits(in);
    }

    public long task1() {
        var blockL = leftReader();
        var blockR = rightReader();

        long checksum = 0;
        long totalFileBlocks = totalFileBlocks();
        int blockId = 0;

        while (blockId < totalFileBlocks) {
            int fileId = fragmenterNextBlock(blockL, blockR) / 2;
            checksum += (long) blockId * fileId;
            blockId++;
        }

        return checksum;
    }

    public long task1a() {
        var blocks = fillBlocks();

        int writeIndex = 0;

        for (int i = 0; i < diskMap.length; i++) {
            if (i % 2 == 0) {
                // file
                for (int j = 0; j < diskMap[i]; j++) {
                    blocks[writeIndex++] = i / 2;
                }
            } else {
                // space
                for (int j = 0; j < diskMap[i]; j++) {
                    blocks[writeIndex++] = FREE_SPACE;
                }
            }
        }

        int l = 0;
        int r = blocks.length - 1;
        while (l < r) {
            if (blocks[l] == FREE_SPACE) {
                while (l < r && blocks[r] == FREE_SPACE) r--;
                if (l < r) {
                    blocks[l] = blocks[r];
                    blocks[r] = FREE_SPACE;
                    l++;
                    r--;
                }
            } else l++;
        }

        return checksum(blocks, r + 1);
    }

    private List<EntryX> initializeDirectory() {
        final List<EntryX> directory = new ArrayList<>();
        int start = 0;
        for (int i = 0; i < diskMap.length; i++) {
            if (i % 2 == 0) {
                directory.add(EntryX.file(i / 2, start, diskMap[i]));
            } else {
                directory.add(EntryX.freeSpace(start, diskMap[i]));
            }
            start += diskMap[i];
        }

        return directory;
    }

    public long task1b() {
        final List<EntryX> directory = initializeDirectory();

        var iterL = directory.listIterator();
        var iterR = directory.listIterator(directory.size());

        while (iterL.hasNext()) {

        }

        return checksum(directory);
    }

    public long task2() {
        var blocks = fillBlocks();

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
                    for (int l = 0; l < fileLength; l++) {
                        blocks[writer++] = rightmostFileThatWillFitIn;
                    }
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

        return checksum(blocks);
    }
}