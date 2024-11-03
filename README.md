# Billing application
### About
A small, simple application designed for issuing invoices for purchased goods. The application uses LaTeX for generating PDF files. It stores information about the goods being sold, clients, and the history of issued invoices. The document template is stored as a separate file and is loaded into the program’s memory at startup, so there is no need to recompile the program if the template is changed. The Qt library was used to create the graphical interface.

The application features a simple and minimalist user interface. The program includes the ability to download updates in case of changes or bug fixes.

### Invoice sample
![image](https://github.com/Marcel129/BillingApplication/assets/62217145/f43144b0-dbfa-4d88-bc5d-403729dff36f)

# Tabs
### Tab "Rachunek" (Invoice)
Basic card used to enter invoice data. Allows you to set the recipient, seller and list of sold goods.
![image](https://github.com/Marcel129/BillingApplication/assets/62217145/7c59bfcb-0a59-452b-8d5b-992ef3716b99)


### Tab "Kontrahenci" (Customers)
The application stores a database of clients. This tab is used for managing their data (adding, deleting, editing). It is possible to add multiple recipients for a single buyer, for example, in cases where the buyer is a local government authority, and the recipient is a subordinate institution.
![image](https://github.com/Marcel129/BillingApplication/assets/62217145/729b76a8-07e7-42f3-a719-a5cd713a9b78)


### Tab "Produkty" (Products)
The program also stores a database of goods for sale. This tab is used for editing them.
![image](https://github.com/Marcel129/BillingApplication/assets/62217145/034400fd-65e9-4983-8451-d224dad4bac4)


### Tab "Rejestr" (Register)
This tab provides a preview of already issued invoices, with the option to retrieve or delete them if needed.
![image](https://github.com/Marcel129/BillingApplication/assets/62217145/9b530dbb-e655-40ac-b6f0-cf70f9d9d830)


