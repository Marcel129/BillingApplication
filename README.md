# Opis
Mała, prosta aplikacja służąca do wystawiania rachunków na zakupione towary. 
Do tworzenia plików PDF wykorzystano skład tekstu LATEX. Program przechowuje informacje odnośnie sprzedawanych towarów, klientów oraz historii wystawionych rachunków. Szablon dokumentu przechowywany jest jako osobny plik - w celu jego zmiany nie ma potrzeby ponownej kompilacji programu. Do stworzenia interfejsu graficznego wykorzystano bibliotekę Qt. 

Aplikacja powstała z myślą o użytkowaniu przez osoby mniej techniczne (np. osoby starsze), ale prowadzące własną działalność gospodarczą i potrzebujace wystawiać rachunki, stąd ograniczona ilość funcji i niezwykle prosty interfejs użytkownika. 

Program wyposażono w możliwość pobierania aktualizacji w razie wprowadzenia zmian/usuwania błędów.

### Przykład wystawionego rachunku
![image](https://github.com/Marcel129/BillingApplication/assets/62217145/f43144b0-dbfa-4d88-bc5d-403729dff36f)


# Karty aplikacji
### Karta "Rachunek"
Podstawowa karta służąca do stworzenia rachunku, wprowadzenia danych wystawcy i odbiorcy oraz listy zakupionych produktów.
![image](https://github.com/Marcel129/BillingApplication/assets/62217145/7c59bfcb-0a59-452b-8d5b-992ef3716b99)


### Karta "Kontrahenci"
Aplikacja przechowuje bazę danych kontrahentów. Zakładka ta służy do zarządzania ich danymi (dodawanie, usuwanie, edycja). Istnieje możliwość dodania kilku odbiorców dla jednego nabywcy w np. przypadku, gdy nabywca jest organ władzy samorządowej, a odbiorcą podległa mu instytucja.
![image](https://github.com/Marcel129/BillingApplication/assets/62217145/729b76a8-07e7-42f3-a719-a5cd713a9b78)


### Karta "Produkty"
Program przechowuje również bazę danych sprzedawanych towarów. Zakładka ta służy do ich edycji.
![image](https://github.com/Marcel129/BillingApplication/assets/62217145/034400fd-65e9-4983-8451-d224dad4bac4)


### Karta "Rejestr"
W zakładce tej dostępny jest podgląd wystawionych już rachunków oraz w razie potrzeby ich odtworzenie lub usunięcie.
![image](https://github.com/Marcel129/BillingApplication/assets/62217145/9b530dbb-e655-40ac-b6f0-cf70f9d9d830)


