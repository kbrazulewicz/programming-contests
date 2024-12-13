package day01;

import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.CsvSource;

import static org.assertj.core.api.Assertions.assertThat;

class HistorianHysteriaTest {

    @ParameterizedTest
    @CsvSource({
        "00.in, 11",
        "01.in, 1580061"
    })
    void totalDistance(String input, long expected) {
        final HistorianHysteria historianHysteria = new HistorianHysteria();
        historianHysteria.parse(getClass().getResourceAsStream(input));

        assertThat(historianHysteria.totalDistance())
            .isEqualTo(expected);
    }

    @ParameterizedTest
    @CsvSource({
        "00.in, 31",
        "01.in, 23046913"
    })
    void similarityScore(String input, long expected) {
        final HistorianHysteria historianHysteria = new HistorianHysteria();
        historianHysteria.parse(getClass().getResourceAsStream(input));

        assertThat(historianHysteria.similarityScore())
            .isEqualTo(expected);
    }
}