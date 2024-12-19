package day08;

import day06.GuardGallivant;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.CsvSource;

import java.io.IOException;

import static org.assertj.core.api.Assertions.assertThat;

public class ResonantCollinearityTest {
    private ResonantCollinearity resonantCollinearity = new ResonantCollinearity();

    @ParameterizedTest
    @CsvSource({
            "00.in, 14",
            "01.in, 4656"
    })
    void task1(String input, long expected) throws IOException {
        resonantCollinearity.parse(getClass().getResourceAsStream(input));

        assertThat(resonantCollinearity.task1())
                .isEqualTo(expected);
    }

}
