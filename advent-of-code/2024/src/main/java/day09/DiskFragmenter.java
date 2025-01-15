package day09;

import commons.IOUtils;

import java.io.IOException;
import java.io.InputStream;

public class DiskFragmenter {

    private int[] diskMap;

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
}