/**
 */
void scanfLineToUnsignedShortArray(unsigned short aBuffer[], size_t aBufferLen)
{
	size_t index = 0;
	int in;
	unsigned char read_digit = 0, read_white = 0;

	while ((in = getchar()) != EOF) {
		if ('0' <= in && in <= '9') {
			if (read_white) {
				if (++index >= aBufferLen) {
					break;
				}
				aBuffer[index] = 0;
			}
			aBuffer[index] *= 10;
			aBuffer[index] += in - '0';

			read_white = 0;
			read_digit = 1;
		} else if (in == ' ' || in == '\t') {
			read_white = 1;
			read_digit = 0;
		} else if (in == '\n') {
			break;
		}
	}
}


/**
 */
void scanfLineToUnsignedIntArray(unsigned int aBuffer[], size_t aBufferLen)
{
	size_t index = 0;
	int in;
	unsigned char read_digit = 0, read_white = 0;

	while ((in = getchar()) != EOF) {
		if ('0' <= in && in <= '9') {
			if (read_white) {
				if (++index >= aBufferLen) {
					break;
				}
				aBuffer[index] = 0;
			}
			aBuffer[index] *= 10;
			aBuffer[index] += in - '0';

			read_white = 0;
			read_digit = 1;
		} else if (in == ' ' || in == '\t') {
			read_white = 1;
			read_digit = 0;
		} else if (in == '\n') {
			break;
		}
	}
} 
