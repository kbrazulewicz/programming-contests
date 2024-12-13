package day05;

import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.CsvSource;

import java.io.IOException;

import static org.assertj.core.api.Assertions.assertThat;

public class PrintQueueTest {
    @ParameterizedTest
    @CsvSource({
            "00.in, 143",
            "01.in, 5991"
    })
    void task1(String input, long expected) throws IOException {
        final PrintQueue printQueue = new PrintQueue();
        printQueue.parse(getClass().getResourceAsStream(input));

        assertThat(printQueue.task1())
                .isEqualTo(expected);
    }
}
