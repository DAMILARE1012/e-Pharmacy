import java.io.BufferedReader;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;

import org.json.simple.JSONArray;
import org.json.simple.JSONObject;
import org.json.simple.parser.JSONParser;
import org.json.simple.parser.ParseException;

public class FileHandler {
    private String filePath;

    // Constructor to initialize the file path
    public FileHandler(String filePath) {
        this.filePath = filePath;
    }

    // Read JSONArray from file
    public JSONArray readJSONArrayFromFile() throws IOException, ParseException {
        JSONParser parser = new JSONParser();
        try (FileReader fileReader = new FileReader(filePath)) {
            if (fileReader.read() == -1) {
                return new JSONArray(); // Return an empty JSONArray if the file is empty
            } else {
                fileReader.close();
                return (JSONArray) parser.parse(new FileReader(filePath));
            }
        } catch (IOException e) {
            return new JSONArray(); // Return an empty JSONArray in case of an exception
        }
    }

    // Write JSONArray to file
    public void writeJSONArrayToFile(JSONArray jsonArray) throws IOException {
        try (FileWriter fileWriter = new FileWriter(filePath)) {
            fileWriter.write(jsonArray.toJSONString()); // Write JSON data to the file
            fileWriter.flush();
            System.out.println("Data written to " + filePath + " successfully!");
        } catch (IOException e) {
            System.out.println("Error while writing data to file: " + e.getMessage());
        }
    }

    // Write Prescription array to file
    public void writePrescriptionsToFile(Prescription[] prescriptions) {
        JSONArray jsonArray = new JSONArray();
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

            jsonArray.add(jsonPrescription);
        }

        try (FileWriter fileWriter = new FileWriter(filePath)) {
            fileWriter.write(jsonArray.toJSONString()); // Write JSON data to the file
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    
}
