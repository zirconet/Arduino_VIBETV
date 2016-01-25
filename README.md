# ARDUINO
# VI_BE_TV

Acquisizione dati da modulo sensore ultrasuoni per gestire sistema allerta e comando IR

COMPONENTI:
Arduino Uno
sensore HC-SR04
led rosso
buzzer


A TV accesa inizializzato il device questi ciclicamente controlla che non ci siano 'ostacoli' entro il suo raggio
di allerta e nel caso, dopo alcuni cicli di controllo, provvede a emettere opportuno segnale IR per lo spegnimento 
della TV. Successivamente se 'ostacolo' non viene più rilevato viene emesso ulteriore segnale IR per la riaccensione 
della TV.
