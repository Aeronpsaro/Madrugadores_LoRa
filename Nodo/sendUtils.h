#define sendBroadcast
  destination = BROADCAST;\
  if(!transmitting && ((millis() - lastSendTime_ms) > txInterval_ms) && firstTime) {\
    transmitting = true;\
    txDoneFlag = false;\
    tx_begin_ms = millis();  \
    uint8_t payload[10];\
    uint8_t payloadLength = 0;\
    payload[payloadLength] = (thisNode.timeGoSleep);  \
    sendMessageBroadcast(payload, payloadLength, msgCount);\
    Serial.println("Sending packet ");\
    Serial.print(msgCount++);\
  }\
    \
  if (transmitting && txDoneFlag) {\
    TxTime_ms = millis() - tx_begin_ms;\
    Serial.print("----> TX completed in ");\
    Serial.print(TxTime_ms);\
    Serial.println(" msecs");\
    \
    // Ajustamos txInterval_ms para respetar un duty cycle del 1% \
    uint32_t lapse_ms = tx_begin_ms - lastSendTime_ms;\
    lastSendTime_ms = tx_begin_ms; \
    float duty_cycle = (100.0f * TxTime_ms) / lapse_ms;\
      \
    Serial.print("Duty cycle: ");\
    Serial.print(duty_cycle, 1);\
    Serial.println(" %\n");\
\
    // Solo si el ciclo de trabajo es superior al 1% lo ajustamos\
    if (duty_cycle > 1.0f) {\
      txInterval_ms = TxTime_ms * 100;\
    }\
      \
    transmitting = false;\
      \
    // Reactivamos la recepción de mensajes, que se desactiva\
    // en segundo plano mientras se transmite\
    LoRa.receive();\
}
