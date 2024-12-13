package day06;

import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.CsvSource;

import java.io.IOException;

import static org.assertj.core.api.Assertions.assertThat;

public class GuardGallivantTest {
    @ParameterizedTest
    @CsvSource({
            "00.in, 41",
            "01.in, 4656"
    })
    void task1(String input, long expected) throws IOException {
        final GuardGallivant guardGallivant = new GuardGallivant();
        guardGallivant.parse(getClass().getResourceAsStream(input));

        assertThat(guardGallivant.task1())
                .isEqualTo(expected);
    }
}
