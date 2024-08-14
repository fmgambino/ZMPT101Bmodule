#include <ZMPT101B.h>

ZMPT101B zmpt101b(35); // Pin donde está conectado el ZMPT101B

void setup() {
    Serial.begin(115200);
    zmpt101b.begin();
}

void loop() {
    float voltage = zmpt101b.readVoltage();
    float frequency = zmpt101b.readFrequency();

    Serial.print("Tensión AC (RMS): ");
    Serial.print(voltage, 2);
    Serial.println(" V");

    Serial.print("Frecuencia AC: ");
    Serial.print(frequency, 2);
    Serial.println(" Hz");

    delay(1000);
}
