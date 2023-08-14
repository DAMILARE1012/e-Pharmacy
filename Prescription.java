import java.io.IOException;
import java.time.LocalDate;
import java.util.ArrayList;

import org.json.simple.JSONArray;
import org.json.simple.JSONObject;
import org.json.simple.parser.ParseException;

public class Prescription {
    private String prescriptionID;
    private String customerID;
    private String doctorName;
    private ArrayList<Medication> medications;
    private LocalDate date;
    private static FileHandler fileHandler = new FileHandler("prescriptions.json");

    // Default constructor
    public Prescription() {
        medications = new ArrayList<>();
        date = LocalDate.now();
    }

    // Parameterized constructor
    public Prescription(String _prescriptionID, String _customerID, String _doctorName, ArrayList<Medication> _medications) {
        prescriptionID = _prescriptionID;
        customerID = _customerID;
        doctorName = _doctorName;
        medications = _medications;
        date = LocalDate.now();
    }

    // Getter methods for private fields
    public String getPrescriptionID() {
        return prescriptionID;
    }

    public String getCustomerID() {
        return customerID;
    }

    public String getDoctorName() {
        return doctorName;
    }

    public ArrayList<Medication> getMedications() {
        return medications;
    }

    public LocalDate getDate() {
        return date;
    }

    // Method to add a prescription
    public void addPrescription() throws IOException, ParseException {
        JSONArray existingPrescriptions = fileHandler.readJSONArrayFromFile();

        // Create a new JSON object for the prescription
        JSONObject prescriptionObject = new JSONObject();
        prescriptionObject.put("PrescriptionID", prescriptionID);
        prescriptionObject.put("CustomerID", customerID);
        prescriptionObject.put("DoctorName", doctorName);
        prescriptionObject.put("Date", date.toString());

        // Create a JSON array for medications
        JSONArray medicationsArray = new JSONArray();
        for (Medication medication : medications) {
            JSONObject medObject = new JSONObject();
            medObject.put("MedicationID", medication.getID());
            medObject.put("Name", medication.getName());
            medObject.put("Price", medication.getPrice()); // Adding price
            medObject.put("Quantity", medication.getQuantity());
            medObject.put("ProcessedStatus", medication.getProcessedStatus());
            medicationsArray.add(medObject);
        }
        prescriptionObject.put("Medications", medicationsArray);

        // Add the prescription object to the existing JSON array and write to file
        existingPrescriptions.add(prescriptionObject);
        fileHandler.writeJSONArrayToFile(existingPrescriptions);
    }

    // Method to view prescriptions
    public static ArrayList<Prescription> viewPrescriptions() throws IOException, ParseException {
        ArrayList<Prescription> prescriptions = new ArrayList<>();
        JSONArray jsonArray = fileHandler.readJSONArrayFromFile();

        // Iterate over JSON array and create Prescription objects
        for (Object obj : jsonArray) {
            JSONObject jsonObject = (JSONObject) obj;
            String doctorName = (String) jsonObject.get("DoctorName");
            String prescriptionID = (String) jsonObject.get("PrescriptionID");
            String customerID = (String) jsonObject.get("CustomerID");
            String dateString = (String) jsonObject.get("Date");
            LocalDate date = LocalDate.parse(dateString);

            JSONArray medicationsArray = (JSONArray) jsonObject.get("Medications");
            ArrayList<Medication> medications = new ArrayList<>();

            // Iterate over medications and create Medication objects
            for (Object medObj : medicationsArray) {
                JSONObject medication = (JSONObject) medObj;
                String medicationID = (String) medication.get("MedicationID");
                String medicationName = (String) medication.get("Name");
                double price = (double) medication.get("Price"); // Retrieving price
                int quantity = Integer.parseInt(medication.get("Quantity").toString());
                boolean processedStatus = (boolean) medication.get("ProcessedStatus");

                medications.add(new Medication(medicationID, medicationName, price, quantity, processedStatus));
            }

            // Create and add Prescription object to the list
            prescriptions.add(new Prescription(prescriptionID, customerID, doctorName, medications));
        }

        return prescriptions;
    }

    // Method to delete a prescription by ID
    public static void deletePrescription(String prescriptionIDToDelete) throws IOException, ParseException {
        JSONArray existingPrescriptions = fileHandler.readJSONArrayFromFile();
        int indexToDelete = -1;

        // Find the index of the prescription to delete
        for (int i = 0; i < existingPrescriptions.size(); i++) {
            JSONObject jsonObject = (JSONObject) existingPrescriptions.get(i);
            String existingPrescriptionID = (String) jsonObject.get("PrescriptionID");

            if (existingPrescriptionID.equals(prescriptionIDToDelete)) {
                indexToDelete = i;
                break;
            }
        }

        // Delete the prescription if found, and update the file
        if (indexToDelete != -1) {
            existingPrescriptions.remove(indexToDelete);
            fileHandler.writeJSONArrayToFile(existingPrescriptions);
            System.out.println("Prescription with ID " + prescriptionIDToDelete + " has been deleted.");
        } else {
            System.out.println("Prescription with ID " + prescriptionIDToDelete + " not found.");
        }
    }
}
