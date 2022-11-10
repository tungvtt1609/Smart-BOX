void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(15,OUTPUT);
  digitalWrite(15,HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(15,LOW);
  delay(5000);
  digitalWrite(15,HIGH);
  delay(5000);
}
