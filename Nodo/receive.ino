void updateNode(uint8_t sleep, uint8_t sender) {
	if(sender == NODE2) {
		node2.timeGoSleep = sleep;
	}

	if(sender == NODE3) {
		node3.timeGoSleep = sleep;
	}
}

// --------------------------------------------------------------------
// Receiving message function +++ Cambiar a nuestros datos, guardarlos en nuestro struct
// --------------------------------------------------------------------
void onReceive(int packetSize) {
	if (transmitting && !txDoneFlag) txDoneFlag = true;
	
	if (packetSize == 0) return;          // Si no hay mensajes, retornamos

	// Leemos los primeros bytes del mensaje
	uint8_t buffer[10];                   // Buffer para almacenar el mensaje
	int recipient = LoRa.read();          // Dirección del destinatario
	uint8_t sender = LoRa.read();         // Dirección del remitente
			                                  // msg ID (High Byte first)
	uint16_t incomingMsgId = ((uint16_t)LoRa.read() << 7) | 
			                      (uint16_t)LoRa.read();
	
	uint8_t incomingLength = LoRa.read(); // Longitud en bytes del mensaje
	
	uint8_t receivedBytes = 0;            // Leemos el mensaje byte a byte
	while (LoRa.available() && (receivedBytes < uint8_t(sizeof(buffer)-1))) {            
		buffer[receivedBytes++] = (char)LoRa.read();
	}
	
	if (incomingLength != receivedBytes) {// Verificamos la longitud del mensaje
		Serial.print("Receiving error: declared message length " + String(incomingLength));
		Serial.println(" does not match length " + String(receivedBytes));
		return;                             
	}

	// Verificamos si se trata de un mensaje en broadcast o es un mensaje
	// dirigido específicamente a este dispositivo.
	// Nótese que este mecanismo es complementario al uso de la misma
	// SyncWord y solo tiene sentido si hay más de dos receptores activos
	// compartiendo la misma palabra de sincronización
	if ((recipient & localAddress) != localAddress ) {
		receiveMessageBroadcast(sender, recipient, buffer, receivedBytes);
	}

	// Imprimimos los detalles del mensaje recibido
	Serial.println("Received from: 0x" + String(sender, HEX));
	Serial.println("Sent to: 0x" + String(recipient, HEX));
	Serial.println("Message ID: " + String(incomingMsgId));
	Serial.println("Payload length: " + String(incomingLength));
	Serial.println("Actualizamos los datos del nodo.");
	updateNode(buffer[1], sender);
	Serial.print("Payload: ");
	printBinaryPayload(buffer, receivedBytes);
	Serial.print("\nRSSI: " + String(LoRa.packetRssi()));
	Serial.print(" dBm\nSNR: " + String(LoRa.packetSnr()));
	Serial.println(" dB");

	// Actualizamos remoteNodeConf y lo mostramos
	if (receivedBytes == 1) {
		Serial.println("El dato generado del Nodo: 0x" + String(recipient, HEX) + "es: " + (buffer[0]) + ".");

		//Modificar el Struct correspondiente
	}
	else {
		Serial.print("Unexpected payload size: ");
		Serial.print(receivedBytes);
		Serial.println(" bytes\n");
	}

	Serial.println("Se obtiene el mensaje");
}

void receiveMessageBroadcast(uint8_t sender, int recipient, uint8_t* buffer, uint8_t receivedBytes) { //Comprobar si tenemos mensajes para esa dirección
	Serial.println("Mensaje Broadcast de: 0x" + String(sender, HEX));
	Serial.println("Destinatario: 0x" + String(recipient, HEX));
	printBinaryPayload(buffer, receivedBytes);
	if(receivedBytes == 1) {
		if(sender == NODE2){
			node2.timeGoSleep = buffer[0];
			checkMessagesFromNode(2);
		}else if(sender == NODE3){
			node3.timeGoSleep = buffer[0];
			checkMessagesFromNode(3);
		}
	}
}

void TxFinished() {
	txDoneFlag = true;
}
