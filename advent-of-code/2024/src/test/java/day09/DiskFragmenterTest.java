package day09;

import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.CsvSource;

import java.io.IOException;

import static org.assertj.core.api.Assertions.assertThat;

public class DiskFragmenterTest {

    private final DiskFragmenter diskFragmenter = new DiskFragmenter();

    @ParameterizedTest
    @CsvSource({
            "00.in, 60",
            "01.in, 1928",
            "02.in, 6310675819476",
    })
    void task1(String input, long expected) throws IOException {
        diskFragmenter.parse(getClass().getResourceAsStream(input));

        assertThat(diskFragmenter.task1())
                .isEqualTo(expected);
    }

    @ParameterizedTest
    @CsvSource({
            "00.in, 0",
            "01.in, 2858",
            "02.in, 0",
    })
    void task2(String input, long expected) throws IOException {
        diskFragmenter.parse(getClass().getResourceAsStream(input));

        assertThat(diskFragmenter.task2())
                .isEqualTo(expected);
    }
}
