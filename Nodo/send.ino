// --------------------------------------------------------------------
// Sending message function
// --------------------------------------------------------------------
void sendMessage(uint8_t* payload, uint8_t payloadLength, uint16_t msgCount) 
{
	Serial.println("Se envia el mensaje");
	while(!LoRa.beginPacket()) {            // Comenzamos el empaquetado del mensaje
		delay(10);                            // 
	}
	LoRa.write(destination);                // Añadimos el ID del destinatario
	LoRa.write(localAddress);               // Añadimos el ID del remitente
	LoRa.write((uint8_t)(msgCount >> 7));   // Añadimos el Id del mensaje (MSB primero)
	LoRa.write((uint8_t)(msgCount & 0xFF)); 
	LoRa.write(payloadLength);              // Añadimos la longitud en bytes del mensaje
	LoRa.write(payload, (size_t)payloadLength); // Añadimos el mensaje/payload 
	LoRa.endPacket(true);                   // Finalizamos el paquete, pero no esperamos a
			                                    // finalice su transmisión
}

void sendMessageBroadcast(uint8_t* payload, uint8_t payloadLength, uint16_t msgCount) { //Mensaje para indicar que estoy despierto
	Serial.println("Pregunto si hay mensajes para mí.");
		while(!LoRa.beginPacket()) {            // Comenzamos el empaquetado del mensaje
		delay(10);                            // 
	}

	LoRa.write(destination); //Broadcast
	LoRa.write(localAddress); //Mi direccion
	LoRa.write((uint8_t)(msgCount >> 7));   // Añadimos el Id del mensaje (MSB primero)
	LoRa.write((uint8_t)(msgCount & 0xFF));
	LoRa.write(payloadLength);              // Añadimos la longitud en bytes del mensaje  
	LoRa.write(payload, (size_t)payloadLength);
	LoRa.endPacket(true);                   // Finalizamos el paquete, pero no esperamos a
			                                    // finalice su transmisión

}


// Genera el dato a enviar PRUEBA
int getData(){
	return random(1,100);
}

// Genera un tiempo random para que se vaya a dormir
int randomTimeSleep() {
	return random(5, 59);
}






4 líneas más; antes #34  21 seconds ago
4 líneas más; antes #34  21 seconds ago
1 Una línea más; antes #33  31 seconds ago
1 Una línea más; antes #33  31 seconds ago
1 una línea menos; después #33  34 seconds ago
1 una línea menos; después #33  34 seconds ago
4 líneas menos; después #34  26 seconds ago
4 líneas menos; después #34  26 seconds ago
4 líneas más; antes #34  27 seconds ago
4 líneas más; antes #34  27 seconds ago
4 fewer lines
4 fewer lines






Este es el cambio más nuevo
4 líneas más; antes #35  50 seconds ago
4 líneas más; antes #35  50 seconds ago
4 líneas menos; después #35  54 seconds ago
4 líneas menos; después #35  54 seconds ago
