package commons;

import org.junit.jupiter.api.Test;

import java.io.ByteArrayInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.nio.charset.StandardCharsets;

import static org.assertj.core.api.Assertions.assertThat;

public class IOUtilsTest {
    @Test
    void parseLineOfDigits() throws IOException {
        InputStream in = new ByteArrayInputStream("1234567890".getBytes(StandardCharsets.UTF_8));
        assertThat(IOUtils.parseLineOfDigits(in))
                .containsExactly(1, 2, 3, 4, 5, 6, 7, 8, 9, 0);
    }
}
