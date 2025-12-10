// IRNET-PRO Modbus UART Sniffer for Arduino Giga R1
// - Serial1 RX: tap master -> sensor line
// - Serial2 RX: tap sensor -> master  line
// - Serial (USB): log to PC
//
// Make sure both Serial1 and Serial2 RX pins are connected to the
// correct UART lines and all grounds are common.

const uint32_t SENSOR_BAUD    = 4800;   // IRNET-PRO refrigerant default
const uint32_t FRAME_GAP_US   = 10000;  // 10 ms idle (new frame time)

struct SniffChannel(
  HardwareSerial &port;
  const char *tag;        // label for this direction (e.g., "M>" or "S<")
  uint32_t lastByteTime;  // last time (micros) a byte was seen
)

SniffChannel chMonitorToSensor = { Serial1, "M>", 0 };    // monitor TX -> sensor rx
SniffChannel chSensorToMonitor = { Serial2, "S<", 0 };    // sensor TX -> monitor rx

// Helper to print a byte as two-digit hex
void printHexByte(uint8_t b) {
  if (b < 0x10) Serial.print('0');
  Serial.print(b, HEX);
}

// Sniff one channel: print hex bytes, tag direction, and mark frams by idle gaps
void sniffChannel(SniffChannel &ch) {
  while (ch.port.available() > 0) {
    uint8_t b = (uint8_t)ch.port.read();
    uint32_t now = micros();

    // If we've been idle for longer than FRAME_GAP_US, then start new frame block
    if (now - ch.lastByteTime > FRAME_GAP_US) {
      Serial.println();
      Serial.print("---- New frame on ");
      Serial.println(ch.tag);
    }
  }
}

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
