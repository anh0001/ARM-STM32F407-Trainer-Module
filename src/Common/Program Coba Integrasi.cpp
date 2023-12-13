#include <Arduino.h>
#include <SPI.h>
#include <SD.h>

// Pin yang digunakan untuk koneksi SD Card
const int chipSelect = 4;

void setup() {
  Serial.begin(9600);

  // Periksa ketersediaan kartu SD
  if (!SD.begin(chipSelect)) {
    Serial.println("Kartu SD tidak ditemukan!");
    while (1);
  }

  Serial.println("Kartu SD ditemukan!");

  // Tulis data ke kartu SD
  writeFile("data.txt", "Hello, SD Card!");

  // Baca data dari kartu SD
  String data = readFile("data.txt");
  Serial.println("Data dari kartu SD: " + data);
}

void loop() {
  // Program utama berada di dalam setup() untuk satu kali eksekusi
}

void writeFile(const char* filename, const char* message) {
  // Buka file untuk penulisan
  File file = SD.open(filename, FILE_WRITE);

  // Periksa kegagalan pembukaan file
  if (file) {
    // Tulis pesan ke file
    file.println(message);
    // Tutup file
    file.close();
    Serial.println("File ditulis dengan sukses!");
  } else {
    Serial.println("Gagal membuka file untuk penulisan!");
  }
}

String readFile(const char* filename) {
  String data = "";

  // Buka file untuk membaca
  File file = SD.open(filename);

  // Periksa kegagalan pembukaan file
  if (file) {
    // Baca data dari file
    while (file.available()) {
      data += (char)file.read();
    }
    // Tutup file
    file.close();
    Serial.println("File dibaca dengan sukses!");
  } else {
    Serial.println("Gagal membuka file untuk membaca!");
  }

  return data;
}
