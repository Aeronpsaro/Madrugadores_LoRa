

void printBinaryPayload(uint8_t * payload, uint8_t payloadLength) {
	flagMessages = payload[0];

	if(flagMessages) {
		for (int i = 2; i < payloadLength; i++) {
			Serial.print(payload[i], DEC);
			Serial.print(payload[i] & 0x0F, DEC);
			Serial.print(" ");
		}
	}
}

