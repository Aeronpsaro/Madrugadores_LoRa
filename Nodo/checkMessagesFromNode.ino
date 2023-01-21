

void checkMessagesFromNode(uint8_t nodo){
	static uint32_t lastSendTime_ms = 0;
	static uint16_t msgCount = 0;
	static uint32_t txInterval_ms = TX_LAPSE_MS;
	static uint32_t tx_begin_ms = 0;
	if(nodo == 2 && (sizeof(node2.listOfMessages)/sizeof(node2.listOfMessages[0])) > 0 && !transmitting && ((millis() - lastSendTime_ms) > txInterval_ms)){
		uint8_t payload[50];
		uint8_t payloadLength = 0;
		payload[payloadLength] = true;
		payload[payloadLength++] = thisNode.timeGoSleep;
		for(byte i = 0; i < 30; i = i +1) {
			payload[payloadLength++] = node2.listOfMessages[i];
		}
		transmitting = true;
		txDoneFlag = false;
		tx_begin_ms = millis();
		destination = NODE2;
		sendMessage(payload, payloadLength, msgCount);
	}else if(nodo == 3 && (sizeof(node3.listOfMessages)/sizeof(node3.listOfMessages[0])) > 0 && !transmitting && ((millis() - lastSendTime_ms) > txInterval_ms)){
		uint8_t payload[5];
		uint8_t payloadLength = 0;
		payload[payloadLength] = true;
		payload[payloadLength++] = thisNode.timeGoSleep;
		for(byte i = 0; i < 30; i = i +1) {
			payload[payloadLength++] = node3.listOfMessages[i];
		}
		transmitting = true;
		txDoneFlag = false;
		tx_begin_ms = millis();
		destination = NODE3;
		sendMessage(payload, payloadLength, msgCount);
	}else if(!transmitting && ((millis() - lastSendTime_ms) > txInterval_ms)){
		if(nodo == 2) {
			destination = NODE2;
		}else {
			destination = NODE3;
		}
		uint8_t payload[5];
		uint8_t payloadLength = 0;
		payload[payloadLength] = false;
		payload[payloadLength++] = thisNode.timeGoSleep;
		transmitting = true;
		txDoneFlag = false;
		tx_begin_ms = millis();
		sendMessage(payload, payloadLength, msgCount);
	}
}

