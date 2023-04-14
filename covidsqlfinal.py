#Saikat Moi 20CS10050

import mysql.connector

mydb = mysql.connector.connect(
  host="10.5.18.69",
  user="20CS10050",
  password="20CS10050",
  database="20CS10050"
)


#sql = "select Physician.Name from Physician,Trained_In,Procedures where Trained_In.Physician=Physician.EmployeeID and Trained_In.Treatment=Procedures.Code and Procedures.Name='bypass surgery';"

q=[]
q.append("select Physician.Name from Physician,Trained_In,Procedures where Trained_In.Physician=Physician.EmployeeID and Trained_In.Treatment=Procedures.Code and Procedures.Name='bypass surgery';")



q.append("select Physician.Name from Physician,Trained_In,Procedures,Department,Affiliated_With where Trained_In.Physician=Physician.EmployeeID and Trained_In.Treatment=Procedures.Code and Procedures.Name='bypass surgery' and Affiliated_With.Physician=Physician.EmployeeID and Affiliated_With.Department=Department.DepartmentID and Department.Name='cardiology';")


q.append("select Nurse.Name from Nurse,Room,On_Call where Nurse.EmployeeID=On_Call.Nurse and On_Call.BlockFloor=Room.BlockFloor and On_Call.BlockCode=Room.BlockCode and Room.RoomNumber='123';")


q.append("select Patient.Name,Patient.Address from Patient,Prescribes,Medication where Patient.SSN=Prescribes.Patient and Prescribes.Medication=Medication.Code and Medication.Name='remdesivir';")


q.append("select Patient.Name,Patient.InsuranceID from Patient,Stay,Room where Patient.SSN=Stay.Patient and Stay.Room=Room.RoomNumber and Room.RoomType='ICU' and extract(day from(Stay.StayEnd-Stay.StayStart))>15;")


q.append("select Nurse.Name from Nurse,Undergoes,Procedures where Nurse.EmployeeID=Undergoes.AssistingNurse and Undergoes.Procedures=Procedures.Code and Procedures.Name='bypass surgery';")


q.append("select Nurse.Name as Nursename,Nurse.Position,Patient.Name as PatientName,Physician.Name as Acc_Physician from Nurse,Undergoes,Procedures,Physician,Patient where Nurse.EmployeeID=Undergoes.AssistingNurse and Undergoes.Procedures=Procedures.Code and Procedures.Name='bypass surgery' and Physician.EmployeeID=Undergoes.Physician and Patient.SSN=Undergoes.Patient;")


q.append("SELECT Name FROM Physician WHERE EmployeeID IN \
   ( SELECT Undergoes.Physician FROM Undergoes LEFT JOIN Trained_In ON Undergoes.Physician=Trained_In.Physician AND Undergoes.Procedures=Trained_In.Treatment\
    WHERE Treatment IS NULL);")
 
      
q.append("SELECT Name FROM Physician WHERE EmployeeID IN \
       ( SELECT Physician FROM Undergoes U \
          WHERE DateUndergoes > \
               (SELECT CertificationExpires \
                    FROM Trained_In T \
                   WHERE T.Physician = U.Physician  AND T.Treatment = U.Procedures ));"  )
               
             
q.append("SELECT P.Name AS Physicianname, Pr.Name AS Procedurename, U.DateUndergoes, Pt.Name AS Patientname\
  FROM Physician P, Undergoes U, Patient Pt, Procedures Pr, Trained_In T\
  WHERE U.Patient = Pt.SSN\
    AND U.Procedures = Pr.Code\
    AND U.Physician = P.EmployeeID\
    AND Pr.Code = T.Treatment\
    AND P.EmployeeID = T.Physician\
    AND U.DateUndergoes > T.CertificationExpires; ")
    
   
q.append("SELECT Pt.Name, PhPCP.Name FROM Patient Pt, Physician PhPCP\
 WHERE Pt.PCP = PhPCP.EmployeeID\
   AND EXISTS\
       (\
         SELECT * FROM Prescribes Pr\
          WHERE Pr.Patient = Pt.SSN\
            AND Pr.Physician = Pt.PCP\
       )\
   AND EXISTS\
       (\
         SELECT * FROM Undergoes U, Procedures Pr\
          WHERE U.Procedures = Pr.Code\
            AND U.Patient = Pt.SSN\
            AND Pr.Cost > 5000\
       )AND 2 <=\
       (\
         SELECT COUNT(A.AppointmentID) FROM Appointment A,Department,Affiliated_With\
          WHERE Affiliated_With.Physician=A.Physician\
            AND Affiliated_With.Department=Department.DepartmentID\
            AND Department.Name='cardiology'\
       )\
   AND NOT Pt.PCP IN\
       (\
          SELECT Head FROM Department);")
                      
 
q.append("with TEMP ( Medication , value) as\
(select Medication , count(patient)\
from Prescribes  \
group by Medication ) ,\
MAX_TABLE( value ) AS \
( SELECT max(value) from TEMP )\
select Medication.name , Medication.brand from Medication , MAX_TABLE , TEMP where Medication.code = TEMP.Medication AND  MAX_TABLE.Value = TEMP.value;")
   

#print(mydb)
mycursor = mydb.cursor()
while 1>0:
    print("Enter Query No To be Executed :")
    Option =input()
    if int(Option) ==13:
        print("Enter the name of the Procedure:")
        Procedure=input()
        newquery="select Physician.Name from Physician,Trained_In,Procedures where Trained_In.Physician=Physician.EmployeeID and Trained_In.Treatment=Procedures.Code and Procedures.Name='"+Procedure+"';"
        print(newquery)
        mycursor.execute(newquery)
        myresult = mycursor.fetchall()
        for x in myresult:
            print(x)
    elif int(Option) ==0:
      print("Exited the Program")
      break
      

    elif int(Option)>0 and int(Option)<14:
        mycursor.execute(q[int(Option)-1])
        if(int(Option)==7):
          print("Nurse  Position Patient Ac_Physician")
        elif(int(Option)==10):
          print("Physician  Procedure  DateUndergoes Patient")
        elif(int(Option)==11):
          print("Patient  Physician")
        elif(int(Option)==12):
          print("Name  Brand") 
        myresult = mycursor.fetchall()
        for x in myresult:
            print(x)
    else:
      print("Invalid Option Selected")
