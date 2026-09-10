// Input devices
#ifdef ENCODER_ACTIVE
void IRAM_ATTR readEncoderISR()  {
  rotaryEncoder->readEncoder_ISR();
}

void RotEncInit()  {
  rotaryEncoder->begin();
  rotaryEncoder->setup(readEncoderISR);
  numberSelector.attachEncoder(rotaryEncoder);
  numberSelector.setRange(0, 100, 1, false, 0);
  numberSelector.setValue(0);
}

void rotary_onButtonClick()  {
  static unsigned long lastTimePressed = 0;
  //ignore multiple press in that time milliseconds
  if (millis() - lastTimePressed < 500)  {
    Serial.println("Buttonpress detected");
    return;
  }
  lastTimePressed = millis();
  Serial.print("button pressed ");
  Serial.print(millis());
  Serial.println(" milliseconds after restart");
}
#endif

// Sensors
#ifdef SHT45Sensor
void initSHT4x(char precision[2], uint8_t heater_lvl, int heater_ms)  {
  screen.print("SHT45-");
  if (! sht4.begin()) {
    Serial.println("Couldn't find SHT4x");
    while (1) delay(1);
  }
  Serial.print("Found SHT4x sensor wth serial number 0x"); Serial.println(sht4.readSerial(), HEX);

  if (strcmp(precision, "H")==0)  {
    sht4.setPrecision(SHT4X_HIGH_PRECISION);
    screen.print("High Precision, ");
    }
  else if (strcmp(precision, "M")==0)  {
    sht4.setPrecision(SHT4X_MED_PRECISION);
    screen.print("Medium Precision, ");
    }
  else  {
    if (strcmp(precision, "L")!=0)  {Serial.println("Invalid temperature precision! Using low precision");}
    screen.print("Low Precision, ");
    sht4.setPrecision(SHT4X_LOW_PRECISION);
  }

  if (heater_lvl==3)  {
    screen.print("High, ");
    if (heater_ms==1000)  {
      sht4.setHeater(SHT4X_HIGH_HEATER_1S);
      screen.println("1s");
      }
    else  {
      sht4.setHeater(SHT4X_HIGH_HEATER_100MS);
      screen.println("100ms");
      if (heater_ms!=100)  {Serial.println("Invalid heater time! Using 100ms.");}
    }
  }
  else if (heater_lvl==2)  {
    screen.print("Medium, ");
    if (heater_ms==1000)  {
      sht4.setHeater(SHT4X_MED_HEATER_1S);
      screen.println("1s");
      }
    else  {
      sht4.setHeater(SHT4X_MED_HEATER_100MS);
      screen.println("100ms");
      if (heater_ms!=100)  {Serial.println("Invalid heater time! Using 100ms.");}
    }
  }
  else if (heater_lvl==1)  {
    screen.print("Low, ");
    if (heater_ms==1000)  {
      sht4.setHeater(SHT4X_LOW_HEATER_1S);
      screen.println("1s");
      }
    else  {
      sht4.setHeater(SHT4X_LOW_HEATER_100MS);
      screen.println("100ms");
      if (heater_ms!=100)  {Serial.println("Invalid heater time! Using 100ms.");}
    }
  }
  else {
    sht4.setHeater(SHT4X_NO_HEATER);
    screen.print("No heater");
    }
}

void changeSHT4x(char precision[2], uint8_t heater_lvl, int heater_ms)  {
  if (strcmp(precision, "H")==0)  {sht4.setPrecision(SHT4X_HIGH_PRECISION);}
  else if (strcmp(precision, "M")==0)  {sht4.setPrecision(SHT4X_MED_PRECISION);}
  else  {
    if (strcmp(precision, "L")!=0)  {Serial.println("Invalid temperature precision! Using low precision");}
    sht4.setPrecision(SHT4X_LOW_PRECISION);
  }

  if (heater_lvl==3)  {
    if (heater_ms==1000)  {sht4.setHeater(SHT4X_HIGH_HEATER_1S);}
    else  {
      sht4.setHeater(SHT4X_HIGH_HEATER_100MS);
      if (heater_ms!=100)  {Serial.println("Invalid heater time! Using 100ms.");}
    }
  }
  else if (heater_lvl==2)  {
    if (heater_ms==1000)  {sht4.setHeater(SHT4X_MED_HEATER_1S);}
    else  {
      sht4.setHeater(SHT4X_MED_HEATER_100MS);
      if (heater_ms!=100)  {Serial.println("Invalid heater time! Using 100ms.");}
    }
  }
  else if (heater_lvl==1)  {
    if (heater_ms==1000)  {sht4.setHeater(SHT4X_LOW_HEATER_1S);}
    else  {
      sht4.setHeater(SHT4X_LOW_HEATER_100MS);
      if (heater_ms!=100)  {Serial.println("Invalid heater time! Using 100ms.");}
    }
  }
  else {
    sht4.setHeater(SHT4X_NO_HEATER);
    }
}

void readSHT4x()  {
  static int counter=0;
  sensors_event_t humidity, temp;
  
  sht4.getEvent(&humidity, &temp);// populate temp and humidity objects with fresh data
  tempCurr = temp.temperature + calibrations.sht4xOffset;
  // static bool countUp = true;                   // Temperature readout testing
  // if (countUp==true)  {
  //   Serial.print("Count up, Temp before:"); Serial.print(tempCurr);
  //   if (tempCurr < 30)  {tempCurr = tempCurr + 0.1;}
  //   else  {countUp = !countUp;}
  // }
  // else  {
  //   Serial.print("Count down, Temp before:"); Serial.print(tempCurr);
  //   if (tempCurr > 1)  {tempCurr = tempCurr - 0.1;}
  //   else  {countUp = !countUp;}
  // }
  // Serial.print(" - Temp after:"); Serial.println(tempCurr);
  humidityCurr = humidity.relative_humidity;
  if (counter==HISTORY_SIZE)  {
    counter = 0;
    // for (int count=HISTORY_SIZE-1; count>=1; count--) {
    //   // Serial.print("Entry "); Serial.print(count); Serial.print(" - "); Serial.print("Old: "); Serial.print(tempHistory[count]); Serial.print(" degC, "); Serial.print(humidHistory[count]); Serial.print("% - New ("); Serial.print(count-1); Serial.print("): "); Serial.print(tempHistory[count-1]); Serial.print(" degC, "); Serial.print(humidHistory[count]); Serial.println("%");
    //   tempHistory[count] = tempHistory[count-1];
    //   humidHistory[count] = humidHistory[count-1];
    //   }
    // Serial.print("Entry 0 - "); Serial.print(tempHistory[0]); Serial.print(" deg C, Humidity: ");Serial.print(humidityCurr, 0); Serial.println("%");
    // Serial.println("\n");
  }
  else {
    tempHistory[counter] = tempCurr;
    humidHistory[counter] = humidityCurr;
    #ifdef NORMTEXT
    Serial.print("Current readings - Temperature: "); Serial.print(tempHistory[counter], 2); Serial.print(" deg C, Humidity: ");Serial.print(humidityCurr, 0); Serial.println("%");
    #endif
    counter++;
  }
}
#endif

#ifdef DS18B20Sensor
void initDS18B20()  {
  timeStart = millis();
  Serial.print("Start Time: "); Serial.println(timeStart);
  while ((readDS18B20()==false)&&(millis()<=timeStart+30000))  {
    Serial.print("Elapsed time: "); Serial.print((millis()-timeStart)/1000); Serial.println("s");
    DS18B20.getAddress(ds18Addr, 0);
    if (ds18Addr!=0)  {
      Serial.print("DS18B20 sensor found at address ");
      for (uint8_t i = 0; i < 8; i++)
      {
        if (ds18Addr[i] < 16);
        Serial.print(ds18Addr[i], HEX);
      }
      Serial.println("h");
    DS18B20.setResolution(ds18Addr, 11);
    }
    else  {
      Serial.println("No sensor found!");
    }
  }
}

bool readDS18B20() {
  #define TWOPTCAL
  //#define OFFSETCAL
  float ds18Temp;

  #ifdef TWOPTCAL
  const float ds18RawRange = calibrations.ds18RawHi - calibrations.ds18RawLo;
  const float ds18RefRange = calibrations.ds18RefHi - calibrations.ds18RefLo;
  #ifdef TEMPDEBUG
  Serial.print("Raw range: "); Serial.print(calibrations.ds18RawHi); Serial.print("-"); Serial.print(calibrations.ds18RawLo); Serial.print("="); Serial.println(ds18RawRange);
  Serial.print("Reference range: "); Serial.print(calibrations.ds18RefHi); Serial.print("-"); Serial.print(calibrations.ds18RefLo); Serial.print("="); Serial.println(ds18RefRange);
  #endif
  #endif

  int count=0;
  #ifdef TEMPDEBUG 
  Serial.println("Reading from DS18B20.");
  #endif
  DS18B20.requestTemperatures();
  ds18Temp = DS18B20.getTempCByIndex(0);
  #ifdef TEMPDEBUG
  Serial.print("Raw reading: "); Serial.println(ds18Temp);
  #endif
  delay(100);
  count ++;
  if (ds18Temp < -60)  {
    Serial.println("Invalid DS18B20 reading.");
  }
  else  {
    #ifdef TWOPTCAL
    tempCurr = ((((ds18Temp - calibrations.ds18RawLo) * ds18RefRange) / ds18RawRange) + calibrations.ds18RefLo);
    #ifdef TEMPDEBUG
    Serial.print("2-point calibrated temperature: "); 
    #endif
    #elif defined OFFSETCAL
    tempCurr = ds18Temp + calibrations.ds18CalOffset;
    #ifdef TEMPDEBUG
    Serial.print("Single offset calibrated temperature: ");
    #endif
    #else
    tempCurr = ds18Temp;
    #ifdef TEMPDEBUG
    Serial.print("Uncalibrated temperature: ");
    #endif
    #endif
    #ifdef TEMPDEBUG
    Serial.println(tempCurr);
    #endif
  }
  if (ds18Temp>-70)  {return true;}
  else  {return false;}
}
#endif

void readTemp()  {
  digitalWrite(pinLED, 1);
  #ifdef DS18B20Sensor
  #ifdef NORMTEXT
  Serial.println("Reading DS18B20 temperature sensor");
  #endif
  readDS18B20();
  #else
    #ifdef BME280Sensor
    #ifdef NORMTEXT
    Serial.println("Reading BME280 temperature/pressure/humidity sensor");
    #endif
    readBME280();
    #else
      #ifdef SHT45Sensor
      #ifdef NORMTEXT
      Serial.println("Reading SHT45 temperature/humidity sensor");
      #endif
      readSHT4x();
      #else
      #ifdef NORMTEXT
      Serial.println("No temperature sensor - using faked temperature");
      #endif
      #endif
    #endif
  #endif
  lastRead = millis();
  digitalWrite(pinLED, 0);
}