package day02;

import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.CsvSource;

import java.io.IOException;

import static org.assertj.core.api.Assertions.assertThat;

class RedNosedReportsTest {

    @ParameterizedTest
    @CsvSource({
        "00.in, 2",
        "01.in, 252"
    })
    void getNumberOfSafeReports(String input, long expected) throws IOException {
        final RedNosedReports redNosedReports = new RedNosedReports();
        redNosedReports.parse(getClass().getResourceAsStream(input));

        assertThat(redNosedReports.getNumberOfSafeReports())
            .isEqualTo(expected);
    }


    @ParameterizedTest
    @CsvSource({
        "00.in, 4",
        "01.in, 324"
    })
    void getNumberOfSafeReportsWithProblemDampener(String input, long expected) throws IOException {
        final RedNosedReports redNosedReports = new RedNosedReports();
        redNosedReports.parse(getClass().getResourceAsStream(input));

        assertThat(redNosedReports.getNumberOfSafeReportsWithProblemDampener())
            .isEqualTo(expected);
    }


}