package day03;

import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.CsvSource;

import java.io.IOException;

import static org.assertj.core.api.Assertions.assertThat;

public class MullItOverTest {
    @ParameterizedTest
    @CsvSource({
        "00.in, 161",
        "01.in, 192767529"
    })
    void mullEverything(String input, long expected) throws IOException {
        final MullItOver mullItOver = new MullItOver();
        mullItOver.parse(getClass().getResourceAsStream(input));

        assertThat(mullItOver.mullEverything())
            .isEqualTo(expected);
    }

    @ParameterizedTest
    @CsvSource({
        "00.in, 161",
        "01.in, 104083373",
        "02.in, 48"
    })
    void mullOnlyEnabled(String input, long expected) throws IOException {
        final MullItOver mullItOver = new MullItOver();
        mullItOver.parse(getClass().getResourceAsStream(input));

        assertThat(mullItOver.mullOnlyEnabled())
            .isEqualTo(expected);
    }
}
