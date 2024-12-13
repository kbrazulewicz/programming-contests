package day04;

import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.CsvSource;

import java.io.IOException;

import static org.assertj.core.api.Assertions.assertThat;

public class CeresSearchTest {
    @ParameterizedTest
    @CsvSource({
        "00.in, 4",
        "01.in, 18",
        "02.in, 2390"
    })
    void xmasPuzzle(String input, long expected) throws IOException {
        final CeresSearch ceresSearch = new CeresSearch();
        ceresSearch.parse(getClass().getResourceAsStream(input));

        assertThat(ceresSearch.xmasPuzzle())
            .isEqualTo(expected);
    }

    @ParameterizedTest
    @CsvSource({
        "03.in, 9",
        "02.in, 1809"
    })
    void masPuzzle(String input, long expected) throws IOException {
        final CeresSearch ceresSearch = new CeresSearch();
        ceresSearch.parse(getClass().getResourceAsStream(input));

        assertThat(ceresSearch.masPuzzle())
            .isEqualTo(expected);
    }
}
