#define DEBUG true  // set to true for debug output to serial, false for no debug ouput
#define DEBUG_SERIAL if(DEBUG)Serial
#include <I2C_16Bit.h>
#include <Wire.h>

#define I2C_ADDR 0x06

// Your register address, which can be found on your IC's datasheet
#define DATA_REGISTER_ADDR 0xff

const byte powerDownPin = 22;

byte previousRegAddr_SR = 0;      // 保存上一次的 regaddr 值（Sample Rate）
byte previousRegAddr_Status = 0; // 保存上一次的 regaddr 值（Status Register）
byte previousRegAddr_ch = 0;    // 保存上一次的 0X03 值（Status Register）


byte ak4118 = 0x13;     // device ak4118, 0010000 = 0x10 (if CAD1=L and CAD0=L, see datasheet p. 50)
// byte ak4118 = 0x11;  // device ak4118, 0010001 = 0x11 (if CAD1=L and CAD0=H, see datasheet p. 50)
// byte ak4118 = 0x12;  // device ak4118, 0010010 = 0x12 (if CAD1=H and CAD0=L, see datasheet p. 50)
// byte ak4118 = 0x13;  // device ak4118, 0010011 = 0x13 (if CAD1=H and CAD0=H, see datasheet p. 50)


byte OLED =0x14;  //1.3"OLED I2C addr,DFR 0.91OLED 显示器
byte ak4497L =0x11; //Lch DAC addr
byte ak4497R =0x12; //Rch DAC addr

void setup() {
  delay(1000);
  DEBUG_SERIAL.begin(115200);
  I2C_16Bit_begin();

  pinMode(powerDownPin, OUTPUT);
  digitalWrite(powerDownPin, HIGH);
  digitalWrite(powerDownPin, LOW); delay(1000);
  digitalWrite(powerDownPin, HIGH); delay(1000);

  AK4118Init(); //初始化AK4118-DIR
  AK4497LInit(); //初始化AK4497L-DAC
  AK4497RInit(); //初始化AK4497R-DAC
  ReadChannelStatus();//读通道状态
  ReadSpdifSR();//读SPDIF采样率
  ReadSpdifStatus();//读SPDIF状态
  
}



//AK4118初始化配寄存器配置信息-----------------------------------------------------------------------------------------------------------------------
void AK4118Init() {

  Wire.beginTransmission(ak4118);
  WriteRegister(ak4118, 0x00, 0x63); //00h:Reset & Initialize(CLK & Power Down Control):
  WriteRegister(ak4118, 0x01, 0x5A); //01h:Format & De-emphasis Control:
  WriteRegister(ak4118, 0x02, 0x88); //02h:Input/ Output Control 0:
  WriteRegister(ak4118, 0x03, 0x48); //03h:Input/ Output Control 1: 0x48=Rx0("default RX0");0x49=Rx1;0x4A=Rx2; 0x4B=Rx3;0x4C=Rx4;0x4D=Rx5;0x4E=Rx6;0x4F=Rx7;
  WriteRegister(ak4118, 0x04, 0xee); //04h:Mask Control for INT0: 
  WriteRegister(ak4118, 0x05, 0xb5); //05h:Mask Control for INT1:
  WriteRegister(ak4118, 0x20, 0x77); //20h:GPIO Control:
  WriteRegister(ak4118, 0x21, 0x00); //21h:GPDR: Pin input/output setting 0:"L"default:Input IO0~I/O7
  WriteRegister(ak4118, 0x22, 0x00); //22h:GPCR: pin output level setting 0:"L"(default)
  WriteRegister(ak4118, 0x23, 0x00); //23h:GPLR: GPD7-0: GPIO pin Input Level Read 0:"L"(default)
  WriteRegister(ak4118, 0x24, 0x3f); //24h:DAT Mask & DTS Detect(default) 
  WriteRegister(ak4118, 0x25, 0xFF); //25h:RX Decete:RXDE7-0: The RX pin Input Detect
  WriteRegister(ak4118, 0x26, 0x03); //26h:STC & DAT Detect:
  WriteRegister(ak4118, 0x28, 0x20); //28h: bit6:1=AK4118A; 0=AK4118
  Wire.endTransmission();
  
}

//AK4497L初始化配寄存器配置信息-----------------------------------------------------------------------------------------------------------------------
void AK4497LInit() {

  Wire.beginTransmission(ak4497L);
  WriteRegister(ak4497L, 0x00, 0x63);  //00h:Reset & Initialize(CLK & Power Down Control):  
  Wire.endTransmission();
}

//AK4497R初始化配寄存器配置信息-----------------------------------------------------------------------------------------------------------------------
void AK4497RInit() {

  Wire.beginTransmission(ak4497R);
  WriteRegister(ak4497R, 0x00, 0x63);  //00h:Reset & Initialize(CLK & Power Down Control):
  Wire.endTransmission();
}


//读03H寄存器检查通道输入状态显示到串口--OK-------------------------------------------------------------------------------------------------------------------
void ReadChannelStatus() { // read channel status
  byte r = 0;
  r = ReadRegister(ak4118, 0x03);

  if (r != previousRegAddr_ch) {
    //DEBUG_SERIAL.print("Sample Rate changed: ");
    switch (r) {
      case 0x48:
        DEBUG_SERIAL.println("RX0"); //输入通道RX0
        break;
      case 0x49:
        DEBUG_SERIAL.println("RX1"); //输入通道RX1
        break;
      case 0x4a:
        DEBUG_SERIAL.println("RX2"); //输入通道RX2
        break;
      case 0x4b:
        DEBUG_SERIAL.println("RX3"); //输入通道RX3
        break;
      case 0x4c:
        DEBUG_SERIAL.println("RX4"); //输入通道RX4
        break;
      case 0x4d:
        DEBUG_SERIAL.println("RX5"); //输入通道RX5
        break;
      case 0x4e:
        DEBUG_SERIAL.println("RX6"); //输入通道RX6
        break;
      case 0x4f:
        DEBUG_SERIAL.println("RX7"); //输入通道RX7
        break;
    }
    
    previousRegAddr_ch = r;
  }
}




//读07H寄存器状态改变并输出到串口--OK-------------------------------------------------------------------------------------------------------------------
void ReadSpdifSR() { // read sample rate
  byte r = 0;
  r = ReadRegister(ak4118, 0x07);

  if (r != previousRegAddr_SR) {
    DEBUG_SERIAL.print("Sample Rate changed: ");
    switch (r) {
      case 0x10:
        DEBUG_SERIAL.println("other");
        break;
      case 0x00:
        DEBUG_SERIAL.println("44.1KHz");
        break;
      case 0x20:
        DEBUG_SERIAL.println("48KHz");
        break;
      case 0x80:
        DEBUG_SERIAL.println("88.2KHz");
        break;
      case 0xa0:
        DEBUG_SERIAL.println("96KHz");
        break;
      case 0xc0:
        DEBUG_SERIAL.println("176.4KHz");
        break;
      case 0xe0:
        DEBUG_SERIAL.println("192KHz");
        break;
      case 4:
        break;
    }
    
    previousRegAddr_SR = r;
  }
}

//读06H寄存器状态改变并输出到串口--OK-------------------------------------------------------------------------------------------------------------------
void ReadSpdifStatus() { // read status register
  byte r = 0;
  r = ReadRegister(ak4118, 0x06);

  if (r != previousRegAddr_Status) {
    //DEBUG_SERIAL.print("Status Register changed: ");
    //PAR: Parity Error or Biphase Error Status D0
    if (bitRead(r, 0) == 1) {DEBUG_SERIAL.println("PAR:Parity error");}  // 1:PAR error
        else if (bitRead(r, 0) == 0) {DEBUG_SERIAL.println("PAR:No Error");} //0:PAR NO error
    //AUDION: Audio Bit Output D1
    if (bitRead(r, 1) == 1) {DEBUG_SERIAL.println("S/PDIF: Non-audio");}  //1:Non-PCM
        else if (bitRead(r, 1) == 0) {DEBUG_SERIAL.println("Audio");} //0:AUDIO
    //PEM: Pre-emphasis Detect.D2
    if (bitRead(r, 2) == 1) {DEBUG_SERIAL.println("S/PDIF: PEM ON");} //1:PEM ON
        else if (bitRead(r, 2) == 0) {DEBUG_SERIAL.println("PEM OFF");} //0:PEM OFF
    //DTSCD: DTS-CD Auto Detect D3
    if (bitRead(r, 3) == 1) {DEBUG_SERIAL.println("S/PDIF: DTS-CD Detect");}     //0:DTS-CD deteced
        else if (bitRead(r, 3) == 0) {DEBUG_SERIAL.println("No Detect DTS-CD");} //0:DTS-CD no deteced
    //UNLCK: PLL Lock Status D4
    if (bitRead(r, 4) == 1) {DEBUG_SERIAL.println("PLL: UnLocked");}        //1:UNLOCK spdif
        else if (bitRead(r, 4) == 0) {DEBUG_SERIAL.println("PLL: LOCKED");} //0:LOCK SPDIF
    //S/PDIF: channel status buffer interrupt D5
    if (bitRead(r, 5) == 1) {DEBUG_SERIAL.println("CINT:Changed");} 
        else if (bitRead(r, 5) == 0) {DEBUG_SERIAL.println("CINT:No Changed");} 
    //AUTO:Non-PCM auto detect D6
    if (bitRead(r, 6) == 0) {DEBUG_SERIAL.println("S/PDIF:Non-PCM signal");}  //0:Non PCM
        else if (bitRead(r, 6) == 1) {DEBUG_SERIAL.println("S/PDIF:PCM");}    //1:PCM
    //QINT:Q-subcode Buffer Interrupt D7
    if (bitRead(r, 7) == 1) {DEBUG_SERIAL.println("Q-sub:Changed");}  
        else if (bitRead(r, 7) == 0) {DEBUG_SERIAL.println("Q-sub:NO Changed");}
    
    previousRegAddr_Status = r;
  }
}


//---------------------------------------------------------------------------------------------------------------------
byte ReadRegister(int devaddr, byte regaddr) { // read a data register value
  Wire.beginTransmission(devaddr);
  Wire.write(regaddr);
  Wire.endTransmission();
  Wire.requestFrom(devaddr, 1);
if (Wire.available()) {return Wire.read();}
 else {return 99;} // if no data in the wire, then return 99 to indicate error
}

void WriteRegister(int devaddr, byte regaddr, byte dataval) { // write a data register value
  Wire.beginTransmission(devaddr); // device
  Wire.write(regaddr); // register
  Wire.write(dataval); // data
  Wire.endTransmission();
}

void ChangeBit(int devaddr, byte regaddr, int data, boolean setting) { // change a single bit in a register
  byte r = ReadRegister(devaddr, regaddr);
  if (setting == 1) {
    bitSet(r, data);
  } else if (setting == 0) {
    bitClear(r, data);
  }
  WriteRegister(devaddr, regaddr, r);
}

void loop() 
{ 
  ReadChannelStatus();
  ReadSpdifSR();
  ReadSpdifStatus();
  delay(100);
 }
