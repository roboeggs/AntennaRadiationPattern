Диаграмма направленности антенны на ESP8266.
Данная установка была разработана в экспрементальных целях.
ESP №1 выступает в виде клиента, который подключен к ESP №2.
ESP №1 устанавливается на установку и имеет подключенный к его пину геркон.
Геркон служит для измерения время прохождения каждого шага.
После измерения данных, данные отправляются по TCP соединению на ESP №2.
Полученные данные принимает программа разрабоная на Python и показывавет диаграмму направленности.
![alt text](https://github.com/roboeggs/ScriptBarcodeScanner/blob/main/images/qr-code.gif)
Модель устаноки.
![Image text](https://github.com/roboeggs/AntennaRadiationPattern/tree/main/images/installation.jpg)