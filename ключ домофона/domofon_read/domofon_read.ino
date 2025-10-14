const byte z = 73;   // размер массива
int t2[73];    // длительность низкий уровень тока или напряжение на Rcч >  400
int t3[73];    // длительность высокий уровень тока или напряжение на Rcч <  400
void setup()
{
  Serial.begin(9600);
  ADCSRA &= B11111000; // очистить три младших бита
  ADCSRA |= B00000100; // установить в них комбинацию 100 что дает делитель 16 и тактовую частоту АЦП 1МГц
}
void loop()
{
  while(analogRead(0)>1000) ; // ждем пока нет ключа
  delay(30);
  // читаем
  memset(t2,0,z); memset(t3,0,z); // обнуляем массив
  unsigned long t=0;
  
  for(int i=0; i<z; i++)
  {
    t= micros();
    while(analogRead(0)>400);
    t2[i]= micros() - t; // длительность начало тайм слота  низкий уровень тока
    
    t= micros();
    while(analogRead(0)<400);
    t3[i]= micros() - t;  // длительность окончание тайм слота  высокий уровень тока
  }
  
  byte Sinhro = 0; // ищем синхробит
  for(int i=0; i<z; i++)
  {
    if (t3[i]>100 )
    {
      if (i<37)
      {
        Sinhro =i+1;
        break; // нашли синхро бит? выходим из цикла
      }
      
    }
  }
  
  
  byte Key[35];
  
  byte q = Sinhro+36 ;
  byte m=0;
  
  for (Sinhro ; Sinhro < q ; Sinhro++)
  {
    if  (  t2[Sinhro] > (t3[Sinhro]+t2[Sinhro]) >> 1)
    Key[m]=1;
    else
    Key[m]=0;
    m++;
  }
  
  bool er=1;
  for (int i=0; i<4; i++)
  {
    
    byte Valid = ( Key[3 +(i<<3)] + Key[4 + (i<<3)] + Key[5 + (i<<3)] + Key[6 + (i<<3)] + Key[7 + (i<<3)]
    + Key[8 + (i<<3)] + Key[9 + (i<<3)] ) % 2;
    
    if ( Valid != Key[10 + (i<<3)] )
    {
      Serial.println("ERROR Read ");
      er=0;
      break;
    }
    
  }
  if (er)
  {
    
    
    if ( Key[2]<<2  |  Key[1]<<1  | Key[0] == 2 )
    Serial.println("-METACOM-  K1233KT2");
    
    Serial.print("KEY HEX = ");
    for(int i=0; i < 4 ; i++)
    {
      byte n= i<<3;
      //byte as = ( Key[9+n]<<6 | Key[8+n]<<5 | Key[7+n]<<4 | Key[6+n]<<3 | Key[5+n]<<2 | Key[4+n]<<1 | Key[3+n] );
      Serial.print( Key[9+n]<<6 | Key[8+n]<<5 | Key[7+n]<<4 | Key[6+n]<<3
      | Key[5+n]<<2 | Key[4+n]<<1 | Key[3+n]  , HEX);
      Serial.print(" ");
    }
  }

  Serial.println("  ");
  Serial.println("  ");
  delay(500);


  
}
