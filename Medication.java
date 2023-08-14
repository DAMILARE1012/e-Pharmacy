public class Medication {

    private String ID;               // Unique identifier for the medication
    private String name;             // Name of the medication
    private String details;          // Additional details or information about the medication
    private String dosage;           // Dosage instructions for the medication
    private double price;            // Price of the medication
    private int quantity;            // Quantity of the medication
    private boolean processedStatus; // Indicates whether the medication has been processed

    // Default constructor
    public Medication() {
    }

    // Parameterized constructor
    public Medication(String _id, String _name, double _price, int _quantity, boolean _processedStatus) {
        this.ID = _id;
        this.name = _name;
        this.price = _price;
        this.quantity = _quantity;
        this.processedStatus = _processedStatus;
    }

    // Getter and Setter methods for private fields

    public String getID() {
        return ID;
    }

    public void setID(String ID) {
        this.ID = ID;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getDetails() {
        return details;
    }

    public void setDetails(String details) {
        this.details = details;
    }

    public String getDosage() {
        return dosage;
    }

    public void setDosage(String dosage) {
        this.dosage = dosage;
    }

    public double getPrice() {
        return price;
    }

    public void setPrice(double price) {
        this.price = price;
    }

    public int getQuantity() {
        return quantity;
    }

    public void setQuantity(int quantity) {
        this.quantity = quantity;
    }

    public boolean getProcessedStatus() {
        return processedStatus;
    }

    public void setProcessedStatus(boolean processedStatus) {
        this.processedStatus = processedStatus;
    }

    // Override toString() method to provide a formatted string representation of the Medication object
    @Override
    public String toString() {
        return "Medication{" +
                "ID='" + ID + '\'' +
                ", name='" + name + '\'' +
                ", details='" + details + '\'' +
                ", dosage='" + dosage + '\'' +
                ", price=" + price +
                ", quantity=" + quantity +
                ", processedStatus=" + processedStatus +
                '}';
    }
}
