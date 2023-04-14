//Saikat Moi
//20CS10050


import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.Scanner;

public class App {
  public static void main(String[] args) {
    Scanner sc = new Scanner(System.in);

    // Prompt the user to select an option

    // Establish a connection to the MySQL database
    Connection connection = null;
    try {
      Class.forName("com.mysql.jdbc.Driver");
      connection = DriverManager.getConnection("jdbc:mysql://10.5.18.69/20CS10050", "20CS10050", "20CS10050");

      // Create a statement object to execute the queries
      Statement statement = connection.createStatement();
    while(1>0){
      System.out.println("Select an option:");
      int option = sc.nextInt();
      if (option == 1) {
        // Option 1: Names of all physicians who are trained in procedure name “bypass surgery”
        ResultSet resultSet = statement.executeQuery("select Physician.Name from Physician,Trained_In,Procedures where Trained_In.Physician=Physician.EmployeeID and Trained_In.Treatment=Procedures.Code and Procedures.Name='bypass surgery';");
        //System.out.println();

        while (resultSet.next()) {
          System.out.println(resultSet.getString("Name"));
        }
      }
      else if (option == 0) {
        System.out.print("Exiting the Program ");
        break;
      } 
      else if (option == 2) {
        
        ResultSet resultSet = statement.executeQuery("select Physician.Name from Physician,Trained_In,Procedures,Department,Affiliated_With where Trained_In.Physician=Physician.EmployeeID and Trained_In.Treatment=Procedures.Code and Procedures.Name='bypass surgery' and Affiliated_With.Physician=Physician.EmployeeID and Affiliated_With.Department=Department.DepartmentID and Department.Name='cardiology';");
        
        while (resultSet.next()) {
          System.out.println(resultSet.getString("Name"));
        }
      }
      else if (option == 3) {
        
        ResultSet resultSet = statement.executeQuery("select Nurse.Name from Nurse,Room,On_Call where Nurse.EmployeeID=On_Call.Nurse and On_Call.BlockFloor=Room.BlockFloor and On_Call.BlockCode=Room.BlockCode and Room.RoomNumber='123';");
        
        while (resultSet.next()) {
          System.out.println(resultSet.getString("Name"));
        }
      }
      else if (option == 4) {
        
        ResultSet resultSet = statement.executeQuery("select Patient.Name,Patient.Address from Patient,Prescribes,Medication where Patient.SSN=Prescribes.Patient and Prescribes.Medication=Medication.Code and Medication.Name='remdesivir';");
        
        while (resultSet.next()) {
          System.out.println(resultSet.getString("Name"));
        }
      }
      else if (option == 5) {
        
        ResultSet resultSet = statement.executeQuery("select Patient.Name,Patient.InsuranceID from Patient,Stay,Room where Patient.SSN=Stay.Patient and Stay.Room=Room.RoomNumber and Room.RoomType='ICU' and extract(day from(Stay.StayEnd-Stay.StayStart))>15;");
        
        while (resultSet.next()) {
          System.out.println(resultSet.getString("Name"));
        }
      }
      else if (option == 6) {
        
        ResultSet resultSet = statement.executeQuery("select Nurse.Name from Nurse,Undergoes,Procedures where Nurse.EmployeeID=Undergoes.AssistingNurse and Undergoes.Procedures=Procedures.Code and Procedures.Name='bypass surgery';");
        
        while (resultSet.next()) {
          System.out.println(resultSet.getString("Name"));
        }
      }
      else if (option == 7) {
        
        ResultSet resultSet = statement.executeQuery("select Nurse.Name as Nursename,Nurse.Position,Patient.Name as PatientName,Physician.Name as Acc_Physician from Nurse,Undergoes,Procedures,Physician,Patient where Nurse.EmployeeID=Undergoes.AssistingNurse and Undergoes.Procedures=Procedures.Code and Procedures.Name='bypass surgery' and Physician.EmployeeID=Undergoes.Physician and Patient.SSN=Undergoes.Patient;");
        System.out.println("Nurse  Position Patient Ac_Physician");
        while (resultSet.next()) {
        String column1 = resultSet.getString("Nursename");
        String column2 = resultSet.getString("Position");
        String column3 = resultSet.getString("PatientName");
        String column4 = resultSet.getString("Acc_Physician");

        System.out.println(column1 + " " + column2 + " " + column3+" "+column4);
        }
      }
      else if (option == 8) {
        
        ResultSet resultSet = statement.executeQuery("SELECT Name FROM Physician WHERE EmployeeID IN ( SELECT Undergoes.Physician FROM Undergoes LEFT JOIN Trained_In ON Undergoes.Physician=Trained_In.Physician AND Undergoes.Procedures=Trained_In.Treatment WHERE Treatment IS NULL);");
        
        while (resultSet.next()) {
          System.out.println(resultSet.getString("Name"));
        }
      }
      else if (option == 9) {
        
        ResultSet resultSet = statement.executeQuery("SELECT Name FROM Physician WHERE EmployeeID IN ( SELECT Physician FROM Undergoes U  WHERE DateUndergoes > (SELECT CertificationExpires FROM Trained_In T WHERE T.Physician = U.Physician  AND T.Treatment = U.Procedures ));");
        
        while (resultSet.next()) {
          System.out.println(resultSet.getString("Name"));
        }
      }
      else if (option == 10) {
        
        ResultSet resultSet = statement.executeQuery("SELECT P.Name AS Physicianname, Pr.Name AS Procedurename, U.DateUndergoes, Pt.Name AS Patientname FROM Physician P, Undergoes U, Patient Pt, Procedures Pr, Trained_In T WHERE U.Patient = Pt.SSN AND U.Procedures = Pr.Code AND U.Physician = P.EmployeeID AND Pr.Code = T.Treatment AND P.EmployeeID = T.Physician AND U.DateUndergoes > T.CertificationExpires; ");
        System.out.println("Physician  Procedure  DateUndergoes Patient");
        while (resultSet.next()) {
        String column1 = resultSet.getString("Physicianname");
        String column2 = resultSet.getString("Procedurename");
        String column3 = resultSet.getString("DateUndergoes");
        String column4 = resultSet.getString("Patientname");

        System.out.println(column1 + " " + column2 + " " + column3+" "+column4);
        }
      }
      else if (option == 11) {
        
        ResultSet resultSet = statement.executeQuery("SELECT Pt.Name, PhPCP.Name FROM Patient Pt, Physician PhPCP WHERE Pt.PCP = PhPCP.EmployeeID AND EXISTS ( SELECT * FROM Prescribes Pr WHERE Pr.Patient = Pt.SSN AND Pr.Physician = Pt.PCP) AND EXISTS(SELECT * FROM Undergoes U, Procedures Pr WHERE U.Procedures = Pr.Code AND U.Patient = Pt.SSN AND Pr.Cost > 5000) AND 2 <= (SELECT COUNT(A.AppointmentID) FROM Appointment A,Department,Affiliated_With WHERE Affiliated_With.Physician=A.Physician AND Affiliated_With.Department=Department.DepartmentID AND Department.Name='cardiology')AND NOT Pt.PCP IN(SELECT Head FROM Department);");
        System.out.println("Patient  Physician");
        while (resultSet.next()) {
          String column1 = resultSet.getString("Pt.Name");
        String column2 = resultSet.getString("PhPCP.Name");
       

        System.out.println(column1 + " " + column2 );
        }
      }
      else if (option == 12) {
        
        ResultSet resultSet = statement.executeQuery("with TEMP ( Medication , value) as(select Medication , count(patient) from Prescribes group by Medication ) ,MAX_TABLE( value ) AS ( SELECT max(value) from TEMP ) select Medication.name , Medication.brand from Medication , MAX_TABLE , TEMP where Medication.code = TEMP.Medication AND  MAX_TABLE.Value = TEMP.value;");
        System.out.println("Name  Brand");
        while (resultSet.next()) {
          String column1 = resultSet.getString("name");
          String column2 = resultSet.getString("brand");
          
  
          System.out.println(column1 + " " + column2 );
        }
      }
       else if (option == 13) {
        
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter the Procedure Name: ");
        String input = scanner.nextLine();
        ResultSet resultSet = statement.executeQuery("select Physician.Name from Physician,Trained_In,Procedures where Trained_In.Physician=Physician.EmployeeID and Trained_In.Treatment=Procedures.Code and Procedures.Name='"+input+"';");
        //scanner.close();
        while (resultSet.next()) {
          System.out.println(resultSet.getString("Name"));
        }
      }
      
      else {
        System.out.println("Invalid option. Please select a valid option.");
      }
    }
   } catch (SQLException | ClassNotFoundException e) {
      e.printStackTrace();
    } finally {
      try {
        if (connection != null) {
          connection.close();
        }
      } catch (SQLException e) {
        e.printStackTrace();
      }
    }
  }
}