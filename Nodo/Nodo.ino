#include <SPI.h>             
#include <LoRa.h>
#include <Arduino_PMIC.h>
#include <RTCZero.h>
#include "sendUtils.h"
#define TX_LAPSE_MS          10000

RTCZero rtc;
//Para controlar el timer
volatile bool no_receive = false;
volatile bool flagMessages = true;
volatile bool firstTime = true;
const uint8_t WAIT = 60;
const uint32_t PATIENCE = 600;
uint32_t TxTime_ms = 0;
int sp_range[6] = {-7, -10, -12, -15, -17, -20};
// NOTA: Ajustar estas variables 
const uint8_t NODE2 = 0x32;
const uint8_t NODE3 = 0x33;
const uint8_t localAddress = 0x31;     // Dirección de este dispositivo
const uint8_t BROADCAST = 0xFF;
uint8_t destination = BROADCAST;         // Dirección de destino, 0xFF es la dirección de broadcast

volatile bool txDoneFlag = true;       // Flag para indicar cuando ha finalizado una transmisión
volatile bool transmitting = false;

// Estructura para almacenar los datos de los nodos externos
typedef struct {
	uint8_t name;
	uint8_t timeGoSleep;
	int message;
	int listOfMessages[30];
	bool haveMessagesForMe;
} LoraDatas_t;

// Estructura para almacenar la configuración de la radio
typedef struct {
	uint8_t bandwidth_index;
	uint8_t spreadingFactor;
	uint8_t codingRate;
	uint8_t txPower; 
} LoRaConfig_t;

double bandwidth_kHz[10] = {7.8E3, 10.4E3, 15.6E3, 20.8E3, 31.25E3,
			                      41.7E3, 62.5E3, 125E3, 250E3, 500E3 };

//LoRaConfig_t thisNodeConf   = { 6, 10, 5, 2};
LoRaConfig_t thisNodeConf   = { 5, 10, 5, 10};
LoRaConfig_t remoteNodeConf = { 0,  0, 0, 0};
LoRaConfig_t prevNodeConf = {0, 0, 0, 0};
int remoteRSSI = 0;
float remoteSNR = 0;

uint8_t bandwidth_new = 5;
uint8_t spreadingFactor_new = 10;
uint8_t codingRate_new = 5;
uint8_t txPower_new = 10;

const int MIN_RSSI = -115;
float MIN_SNR = -7;

//Configuracion Nodo
LoraDatas_t thisNode = {1, randomTimeSleep(), NULL, NULL, false};
LoraDatas_t node2 = {2, NULL, NULL, NULL, false};
LoraDatas_t node3 = {3, NULL, NULL, NULL, false};

void loop() {
	// put your main code here, to run repeatedly:
	static uint32_t lastSendTime_ms = 0;
	static uint16_t msgCount = 0;
	static uint32_t txInterval_ms = TX_LAPSE_MS;
	static uint32_t tx_begin_ms = 0;
	//Broadcast
	sendBroadcast;
	firstTime = false;

	if(!flagMessages) {
		//Generamos el dato
		int dato = getData();
		thisNode.message = dato;
		//Broadcast
		sendBroadcast;
		//Comprobar si la dirección es mi destino (enviar) con un random

		//Comprobar si su tiempo es > que el mío, le mando el dato y sleep sino, que me envíe sus datos
	}
}
