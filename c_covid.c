#include <stdio.h>
#include <mysql/mysql.h>
#include<string.h>
int main()
{
    int option;
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    char *server = "10.5.18.69";
    char *user = "20CS10050";
    char *password = "20CS10050"; /* set me first */
    char *database = "20CS10050";

    conn = mysql_init(NULL);

    /* Connect to database */
    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0))
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return 1;
    }

    /* Get user option */
   
   

    /* Execute the appropriate query based on user option */
    int flag=1;
    char query[500];
    char first[]="select Physician.Name from Physician,Trained_In,Procedures where Trained_In.Physician=Physician.EmployeeID and Trained_In.Treatment=Procedures.Code and Procedures.Name='";
    char last[]="';";
    char input[100];
    while(flag){
    printf("Enter option number :\n"); 
    scanf("%d", &option);
    switch(option)
    {
    
        case 0:
             printf("Exited from the Program\n");
             flag=0;
             continue;
             break;
    
        case 1:
            /* Option 1 */
            if (mysql_query(conn,"select Physician.Name from Physician,Trained_In,Procedures where Trained_In.Physician=Physician.EmployeeID and Trained_In.Treatment=Procedures.Code and Procedures.Name='bypass surgery';" ))
            {
                fprintf(stderr, "%s\n", mysql_error(conn));
                return 1;
            }
            break;
        case 2:
            /* Option 2 */
            if (mysql_query(conn,"select Physician.Name from Physician,Trained_In,Procedures,Department,Affiliated_With where Trained_In.Physician=Physician.EmployeeID and Trained_In.Treatment=Procedures.Code and Procedures.Name='bypass surgery' and Affiliated_With.Physician=Physician.EmployeeID and Affiliated_With.Department=Department.DepartmentID and Department.Name='cardiology';" ))
            {
                fprintf(stderr, "%s\n", mysql_error(conn));
                return 1;
            }
            break;
         case 3:
            /* Option 2 */
            if (mysql_query(conn, "select Nurse.Name from Nurse,Room,On_Call where Nurse.EmployeeID=On_Call.Nurse and On_Call.BlockFloor=Room.BlockFloor and On_Call.BlockCode=Room.BlockCode and Room.RoomNumber='123';"))
            {
                fprintf(stderr, "%s\n", mysql_error(conn));
                return 1;
            }
            break;
         case 4:
            /* Option 2 */
            if (mysql_query(conn, "select Patient.Name,Patient.Address from Patient,Prescribes,Medication where Patient.SSN=Prescribes.Patient and Prescribes.Medication=Medication.Code and Medication.Name='remdesivir';"))
            {
                fprintf(stderr, "%s\n", mysql_error(conn));
                return 1;
            }
            break; 
         case 5:
            /* Option 2 */
            if (mysql_query(conn, "select Patient.Name,Patient.InsuranceID from Patient,Stay,Room where Patient.SSN=Stay.Patient and Stay.Room=Room.RoomNumber and Room.RoomType='ICU' and extract(day from(Stay.StayEnd-Stay.StayStart))>15;"))
            {
                fprintf(stderr, "%s\n", mysql_error(conn));
                return 1;
            }
            break; 
            case 6:
            /* Option 2 */
            if (mysql_query(conn, "select Nurse.Name from Nurse,Undergoes,Procedures where Nurse.EmployeeID=Undergoes.AssistingNurse and Undergoes.Procedures=Procedures.Code and Procedures.Name='bypass surgery';"))
            {
                fprintf(stderr, "%s\n", mysql_error(conn));
                return 1;
            }
            break;    
            
        case 7:
            /* Option 2 */
            printf("Nurse	Position	Patient	Ac_Physician\n");
            if (mysql_query(conn, "select Nurse.Name as Nursename,Nurse.Position,Patient.Name as PatientName,Physician.Name as Acc_Physician from Nurse,Undergoes,Procedures,Physician,Patient where Nurse.EmployeeID=Undergoes.AssistingNurse and Undergoes.Procedures=Procedures.Code and Procedures.Name='bypass surgery' and Physician.EmployeeID=Undergoes.Physician and Patient.SSN=Undergoes.Patient;"))
            {
                fprintf(stderr, "%s\n", mysql_error(conn));
                return 1;
            }
            break; 
         case 8:
            /* Option 2 */
            if (mysql_query(conn, "SELECT Name FROM Physician WHERE EmployeeID IN ( SELECT Undergoes.Physician FROM Undergoes LEFT JOIN Trained_In ON Undergoes.Physician=Trained_In.Physician AND Undergoes.Procedures=Trained_In.Treatment WHERE Treatment IS NULL);"))
            {
                fprintf(stderr, "%s\n", mysql_error(conn));
                return 1;
            }
            break;   
         
        case 9:
            /* Option 2 */
            if (mysql_query(conn, "SELECT Name FROM Physician WHERE EmployeeID IN \
       ( SELECT Physician FROM Undergoes U \
          WHERE DateUndergoes > \
               (SELECT CertificationExpires \
                    FROM Trained_In T \
                   WHERE T.Physician = U.Physician  AND T.Treatment = U.Procedures ));"))
            {
                fprintf(stderr, "%s\n", mysql_error(conn));
                return 1;
            }
            break; 
       case 10:
            /* Option 2 */
            printf("Physician	Procedure	DateUndergoes	Patient\n");
            if (mysql_query(conn, "SELECT P.Name AS Physicianname, Pr.Name AS Procedurename, U.DateUndergoes, Pt.Name AS Patientname\
  FROM Physician P, Undergoes U, Patient Pt, Procedures Pr, Trained_In T\
  WHERE U.Patient = Pt.SSN\
    AND U.Procedures = Pr.Code\
    AND U.Physician = P.EmployeeID\
    AND Pr.Code = T.Treatment\
    AND P.EmployeeID = T.Physician\
    AND U.DateUndergoes > T.CertificationExpires; "))
            {
                fprintf(stderr, "%s\n", mysql_error(conn));
                return 1;
            }
            break;
        case 11:
            /* Option 2 */
            printf("Patient	Physician\n");
            if (mysql_query(conn, "SELECT Pt.Name, PhPCP.Name FROM Patient Pt, Physician PhPCP\
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
          SELECT Head FROM Department);"))
            {
                fprintf(stderr, "%s\n", mysql_error(conn));
                return 1;
            }
            break; 
            
     case 12:
            /* Option 2 */
            printf("Name 	Brand\n");
            if (mysql_query(conn, "with TEMP ( Medication , value) as\
(select Medication , count(patient)\
from Prescribes  \
group by Medication ) ,\
MAX_TABLE( value ) AS \
( SELECT max(value) from TEMP )\
select Medication.name , Medication.brand from Medication , MAX_TABLE , TEMP where Medication.code = TEMP.Medication AND  MAX_TABLE.Value = TEMP.value;"))
            {
                fprintf(stderr, "%s\n", mysql_error(conn));
                return 1;
            }
            break;            
        case 13:
        
        fgets(input,100,stdin);
        //scanf("%[^\n]",input);
        //scanf("%s",input);
       // printf("%s",input);
        sprintf(query,"select Physician.Name from Physician,Trained_In,Procedures where Trained_In.Physician=Physician.EmployeeID and Trained_In.Treatment=Procedures.Code and Procedures.Name='%s';",input);
        //printf("%s",query);
        //strcat(first,input);
        //strcat(first,last);
       // printf("%s",first);
        if (mysql_query(conn, query))
            {
                fprintf(stderr, "%s\n", mysql_error(conn));
                return 1;
            }
            break;
                      
        default:
            /* Invalid option */
            printf("Invalid option. Please enter valid Choice.\n");
            continue;
            
    }
    

    /* Output the results */
    res = mysql_use_result(conn);
    //printf("Name\n");
    while ((row = mysql_fetch_row(res)) != NULL)
    {
       if(option==7){
       printf("%s	%s	%s	%s\n", row[0],row[1],row[2],row[3]);
       }
       
       else if(option==10){
       printf("%s	%s	%s	%s\n", row[0],row[1],row[2],row[3]);
       }
       else if (option==11 || option==12){
       printf("%s	%s\n", row[0],row[1]);
       }
       else{
        printf("%s\n", row[0]);
        }
    }
    mysql_free_result(res);
    }

    /* Close connection */
    mysql_close(conn);

    return 0;
}
