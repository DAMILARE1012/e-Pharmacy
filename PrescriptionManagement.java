import java.io.*;
import java.time.LocalDate;
import java.util.ArrayList;
import java.util.Scanner;
import org.json.simple.*;
import org.json.simple.parser.JSONParser;
import org.json.simple.parser.ParseException;
import java.util.InputMismatchException;

// WE USED CHATGPT TO ADJUST TABLES DISPLAY AVAILABLE MEDICATIONS, AND VIEW PRESCRIPTIONS. AND TO UNDERSTAND SOME LIBRARIES IMPORTED.
// Here are some prompts technique i used to get some basic understandings:
// JSON File Handling: "We've used a JSONFileHandler class to handle reading and writing prescription data and medication information from/to JSON files. Could you please provide feedback on our JSON file handling approach?"
//Viewing and Deleting Prescriptions: "We've implemented functionality to view prescriptions in a tabular format and to delete prescriptions based on the provided prescription ID. Could you please review the implementation and suggest any optimizations?"
// Error Handling and Exception Management: "We've implemented error handling and exception management, including handling input mismatches and JSON parsing exceptions. Could you please review our error handling approach and suggest improvements?"

public class PrescriptionManagement {

    public static void main(String[] args) throws IOException {
        Scanner scanner = new Scanner(System.in);
        int choice;
        ArrayList<Prescription> prescriptions = new ArrayList<>();

        JSONFileHandler fileHandler = new JSONFileHandler("prescriptions.json");

        // Load existing prescriptions from the file
        Prescription[] prescriptionArray = fileHandler.readPrescriptionsFromFile();
        for (Prescription prescription : prescriptionArray) {
            prescriptions.add(prescription);
        }

        while (true) {
            displayMainMenu();
            try {
                choice = scanner.nextInt();
                scanner.nextLine(); // Consume newline

                switch (choice) {
                    case 1:
                        Prescription newPrescription = createPrescription(scanner, fileHandler);
                        prescriptions.add(newPrescription);
                        fileHandler.writePrescriptionsToFile(prescriptions.toArray(new Prescription[0]));
                        System.out.println("Data written to prescriptions.json successfully!");
                        break;
                    case 2:
                        viewPrescriptions(prescriptions);
                        break;
                    case 3:
                        deletePrescription(scanner, prescriptions);
                        fileHandler.writePrescriptionsToFile(prescriptions.toArray(new Prescription[0]));
                        break;
                    case 4:
                        System.out.println("Exiting the Prescription Management section...");
                        System.exit(0);
                        break;
                    default:
                        System.out.println("Invalid choice. Please try again.");
                }
            } catch (InputMismatchException e) {
                System.out.println("Invalid input. Please enter a valid integer choice.");
                scanner.nextLine(); // Clear the input buffer
            }
        }
    }

    // Create a new prescription
    private static Prescription createPrescription(Scanner scanner, JSONFileHandler fileHandler) {
        Prescription prescription = new Prescription();

        System.out.print("Enter Prescription ID: ");
        String prescriptionID = scanner.nextLine();
        prescription.setPrescriptionID(prescriptionID);

        System.out.print("Enter Customer ID: ");
        String customerID = scanner.nextLine();
        prescription.setCustomerID(customerID);

        System.out.print("Enter Doctor's Name: ");
        String doctorName = scanner.nextLine();
        prescription.setDoctorName(doctorName);

        prescription.setDate(LocalDate.now());

        int numMedications;
        while (true) {
            System.out.print("Enter the number of medications to add: ");
            try {
                numMedications = scanner.nextInt();
                scanner.nextLine(); // Consume newline
                break; // Exit the loop if a valid integer is entered
            } catch (InputMismatchException e) {
                System.out.println("Invalid input. Please enter a valid integer for the number of medications.");
                scanner.nextLine(); // Clear the input buffer
            }
        }

        displayAvailableMedications(fileHandler);

        ArrayList<Medication> medications = new ArrayList<>();
        for (int i = 0; i < numMedications; i++) {
            System.out.println("Enter details for Medication " + (i + 1) + ":");
            System.out.print("Enter Medication ID: ");
            String medicationID = scanner.nextLine();
            System.out.print("Enter Medication Name: ");
            String medicationName = scanner.nextLine();
            System.out.print("Enter Medication Details: ");
            String medicationDetails = scanner.nextLine();
            System.out.print("Enter Dosage: ");
            String dosage = scanner.nextLine();

            int quantity;
            while (true) {
                System.out.print("Enter Quantity: ");
                try {
                    quantity = scanner.nextInt();
                    scanner.nextLine(); // Consume newline
                    break; // Exit the loop if a valid integer is entered
                } catch (InputMismatchException e) {
                    System.out.println("Invalid input. Please enter a valid integer for the quantity.");
                    scanner.nextLine(); // Clear the input buffer
                }
            }

            Medication medication = new Medication(medicationID, medicationName, medicationDetails, dosage, quantity);
            medications.add(medication);
        }
        prescription.setMedications(medications);

        return prescription;
    }

    // Display available medications
    private static void displayAvailableMedications(JSONFileHandler fileHandler) {
        JSONArray jsonArray = fileHandler.readJSONArrayFromFile("product.json");

        System.out.println("---------------------------------------------------------------------------");
        System.out.println("| Medication ID| Medication Name | Medication Price || Medication Quantity|");
        System.out.println("---------------------------------------------------------------------------");

        for (Object obj : jsonArray) {
            JSONObject jsonObject = (JSONObject) obj;
            String medicationID = (String) jsonObject.get("code");
            String medicationName = (String) jsonObject.get("name");

            // Parse the price field as a double
            double medicationPrice = Double.parseDouble((String) jsonObject.get("price"));

            // Parse the quantity field as a long
            long medicationQuantity = Long.parseLong((String) jsonObject.get("quantity"));

            System.out.printf("| %-13s| %-15s| %-17.2f|| %-17d|\n", medicationID, medicationName, medicationPrice, medicationQuantity);
        }

        System.out.println("---------------------------------------------------------------------------");
    }

    // View prescriptions
    private static void viewPrescriptions(ArrayList<Prescription> prescriptions) {
        if (prescriptions.isEmpty()) {
            System.out.println("No prescriptions available\n");
        } else {
            System.out.println("--------------------------------------------------------------------------------------");
            System.out.println("| Prescription ID | Doctor Name         | Customer ID         | Date                |");
            System.out.println("--------------------------------------------------------------------------------------");

            for (Prescription p : prescriptions) {
                System.out.printf("| %-16s| %-20s| %-20s| %-20s|\n",
                        p.getPrescriptionID(), p.getDoctorName(), p.getCustomerID(), p.getDate());
                System.out.println("--------------------------------------------------------------------------------------");
            }
        }
    }

    // Delete a prescription
    private static void deletePrescription(Scanner scanner, ArrayList<Prescription> prescriptions) {
        System.out.print("Enter Prescription ID to delete: ");
        String prescriptionIDToDelete = scanner.nextLine();

        Prescription prescriptionToRemove = null;
        for (Prescription prescription : prescriptions) {
            if (prescription.getPrescriptionID().equals(prescriptionIDToDelete)) {
                prescriptionToRemove = prescription;
                break;
            }
        }
        if (prescriptionToRemove != null) {
            prescriptions.remove(prescriptionToRemove);
            System.out.println("Prescription with ID " + prescriptionIDToDelete + " has been deleted.");
        } else {
            System.out.println("Prescription with ID " + prescriptionIDToDelete + " not found.");
        }
    }

    // Display main menu options
    private static void displayMainMenu() {
        System.out.println("Welcome Menu");
        System.out.println("1. Add a prescription");
        System.out.println("2. View prescriptions");
        System.out.println("3. Delete prescriptions");
        System.out.println("4. Exit");
        System.out.print("Enter your choice: ");
    }

    // JSON file handling
    private static class JSONFileHandler {
        private String filePath;

        public JSONFileHandler(String filePath) {
            this.filePath = filePath;
        }

        public Prescription[] readPrescriptionsFromFile() {
            JSONParser parser = new JSONParser();
            try (FileReader fileReader = new FileReader(filePath)) {
                JSONArray jsonArray = (JSONArray) parser.parse(fileReader);
                Prescription[] prescriptions = new Prescription[jsonArray.size()];
                for (int i = 0; i < jsonArray.size(); i++) {
                    JSONObject jsonPrescription = (JSONObject) jsonArray.get(i);
                    Prescription prescription = new Prescription();
                    prescription.setPrescriptionID((String) jsonPrescription.get("PrescriptionID"));
                    prescription.setDoctorName((String) jsonPrescription.get("DoctorName"));
                    prescription.setCustomerID((String) jsonPrescription.get("CustomerID"));
                    prescription.setDate(LocalDate.parse((String) jsonPrescription.get("Date")));
                    JSONArray jsonMedications = (JSONArray) jsonPrescription.get("Medications");
                    ArrayList<Medication> medications = new ArrayList<>();
                    for (Object obj : jsonMedications) {
                        JSONObject jsonMedication = (JSONObject) obj;
                        String medicationID = (String) jsonMedication.get("ID");
                        String name = (String) jsonMedication.get("Name");
                        String details = (String) jsonMedication.get("Details");
                        String dosage = (String) jsonMedication.get("Dosage");
                        long quantity = (long) jsonMedication.get("Quantity");
                        Medication medication = new Medication(medicationID, name, details, dosage, (int) quantity);
                        medications.add(medication);
                    }
                    prescription.setMedications(medications);
                    prescriptions[i] = prescription;
                }
                return prescriptions;
            } catch (Exception e) {
                return new Prescription[0];
            }
        }

        public void writePrescriptionsToFile(Prescription[] prescriptions) {
            try (FileWriter fileWriter = new FileWriter(filePath)) {
                for (Prescription prescription : prescriptions) {
                    JSONObject jsonPrescription = new JSONObject();
                    jsonPrescription.put("PrescriptionID", prescription.getPrescriptionID());
                    jsonPrescription.put("DoctorName", prescription.getDoctorName());
                    jsonPrescription.put("CustomerID", prescription.getCustomerID());
                    jsonPrescription.put("Date", prescription.getDate().toString());

                    JSONArray jsonMedications = new JSONArray();
                    for (Medication medication : prescription.getMedications()) {
                        JSONObject jsonMedication = new JSONObject();
                        jsonMedication.put("ID", medication.getID());
                        jsonMedication.put("Name", medication.getName());
                        jsonMedication.put("Details", medication.getDetails());
                        jsonMedication.put("Dosage", medication.getDosage());
                        jsonMedication.put("Quantity", medication.getQuantity());
                        jsonMedications.add(jsonMedication);
                    }
                    jsonPrescription.put("Medications", jsonMedications);

                    fileWriter.write(jsonPrescription.toJSONString() + "\n"); // Write with a newline
                }
            } catch (IOException e) {
                e.printStackTrace();
            }
        }

        public JSONArray readJSONArrayFromFile(String fileName) {
            JSONParser parser = new JSONParser();
            try (FileReader fileReader = new FileReader(fileName)) {
                return (JSONArray) parser.parse(fileReader);
            } catch (Exception e) {
                e.printStackTrace();
                return new JSONArray();
            }
        }
    }

    // Medication class to represent a medication item
    private static class Medication {
        private String ID;
        private String name;
        private String details;
        private String dosage;
        private int quantity;

        public Medication(String ID, String name, String details, String dosage, int quantity) {
            this.ID = ID;
            this.name = name;
            this.details = details;
            this.dosage = dosage;
            this.quantity = quantity;
        }

        public String getID() {
            return ID;
        }

        public String getName() {
            return name;
        }

        public String getDetails() {
            return details;
        }

        public String getDosage() {
            return dosage;
        }

        public int getQuantity() {
            return quantity;
        }
    }

    // Prescription class to represent a prescription
    private static class Prescription {
        private String prescriptionID;
        private String customerID;
        private String doctorName;
        private LocalDate date;
        private ArrayList<Medication> medications;

        public Prescription() {
            medications = new ArrayList<>();
        }

        public void setPrescriptionID(String prescriptionID) {
            this.prescriptionID = prescriptionID;
        }

        public void setCustomerID(String customerID) {
            this.customerID = customerID;
        }

        public void setDoctorName(String doctorName) {
            this.doctorName = doctorName;
        }

        public void setDate(LocalDate date) {
            this.date = date;
        }

        public void setMedications(ArrayList<Medication> medications) {
            this.medications = medications;
        }

        public String getPrescriptionID() {
            return prescriptionID;
        }

        public String getCustomerID() {
            return customerID;
        }

        public String getDoctorName() {
            return doctorName;
        }

        public LocalDate getDate() {
            return date;
        }

        public ArrayList<Medication> getMedications() {
            return medications;
        }
    }
}
