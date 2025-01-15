package day08;

import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.CsvSource;

import java.io.IOException;

import static org.assertj.core.api.Assertions.assertThat;

public class ResonantCollinearityTest {
    private final ResonantCollinearity resonantCollinearity = new ResonantCollinearity();

    @ParameterizedTest
    @CsvSource({
            "00.in, 14",
            "01.in, 413"
    })
    void task1(String input, long expected) throws IOException {
        resonantCollinearity.parse(getClass().getResourceAsStream(input));

        assertThat(resonantCollinearity.task1())
                .isEqualTo(expected);
    }

    @ParameterizedTest
    @CsvSource({
            "00.in, 34",
            "01.in, 1417"
    })
    void task2(String input, long expected) throws IOException {
        resonantCollinearity.parse(getClass().getResourceAsStream(input));

        assertThat(resonantCollinearity.task2())
                .isEqualTo(expected);
    }

}
