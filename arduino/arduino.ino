
#include <MFRC522.h>
//#include <SPI.h>


#define RE_PIN   A0 //讀卡機的重置位置
#define S_PIN    10 //晶片選擇位置
MFRC522 mfrc522(S_PIN , RE_PIN);    //constructer
MFRC522::StatusCode status_now;

void setup(){
    Serial.begin(9600);
    Serial.println("This is its UID:");
    mfrc522.PCD_Init();
    
    

}

void loop(){
    if(mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()){
        byte *id = mfrc522.uid.uidByte;   // 取得卡片的UID
        byte idSize = mfrc522.uid.size;   // 取得UID的長度 
        
        Serial.print("PICC type: ");      // 顯示卡片類型
      // 根據卡片回應的SAK值（mfrc522.uid.sak）判斷卡片類型
      MFRC522::PICC_Type piccType = mfrc522.PICC_GetType(mfrc522.uid.sak);
      Serial.println(mfrc522.PICC_GetTypeName(piccType));
 
      Serial.print("UID Size: ");       // 顯示卡片的UID長度值
      Serial.println(idSize);
 
      for (byte i = 0; i < idSize; i++) {  // 逐一顯示UID碼
        Serial.print("id[");
        Serial.print(i);
        Serial.print("]: ");
        Serial.println(id[i], HEX);       // 以16進位顯示UID值
      }
      Serial.println();
      delay(5000);
      
      // 開始寫資料
    byte uid[5] = {0xE2, 0xC3, 0x0A, 0x08, 0x23}; 
    status_now = (MFRC522::StatusCode) mfrc522.MIFARE_Write(0, uid,5);
    
    if(status_now != MFRC522::STATUS_OK){
        Serial.print(F("MIFARE_Write() failed: "));
        Serial.println(mfrc522.GetStatusCodeName(status_now));
        return;
    }
    Serial.print("OK\n");
    
    *id = mfrc522.uid.uidByte;
    
    for (byte i = 0; i < idSize; i++) {  // 逐一顯示UID碼
        Serial.print("id[");
        Serial.print(i);
        Serial.print("]: ");
        Serial.println(id[i], HEX);       // 以16進位顯示UID值
      }
      Serial.println();
      
    }
    
    mfrc522.PICC_HaltA();
    
}

