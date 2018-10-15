/*TESTING INSERT PROCEDURES*/
SELECT * FROM certification WHERE id = 'kidney1'
EXEC add_certification @id = ‘kidney1’, @overview = ‘lekarz specjalizuje siê w leczeniu
chorob nerek’
SELECT * FROM certification WHERE id = 'kidney1'
GO
SELECT * FROM proceduretype WHERE personel = 5
EXEC add_proceduretype @overview = 'Ucinanie reki zarazonej gangrena', @personel = 5
SELECT * FROM proceduretype WHERE personel = 5
GO
SELECT * FROM department WHERE dep_name = 'Stomatologia'
EXEC add_department1 @dep_name = 'Stomatologia'
SELECT * FROM department WHERE dep_name = 'Stomatologia'
GO
SELECT * FROM room r JOIN department d ON r.department_id = d.id WHERE r.id = 999
EXEC add_room2 @room_number = 999, @dep_id = 2, @maxspace = 6
SELECT * FROM room r JOIN department d ON r.department_id = d.id WHERE r.id = 999
GO
SELECT * FROM medicalpersonel WHERE firstname = 'TEST'
EXEC add_medicalpersonel @firstname = 'TEST', @surname = 'TESTOWY', @dep_id = 1, @cert_id =
'uro1'
SELECT * FROM medicalpersonel WHERE firstname = 'TEST'
GO
SELECT * FROM procedurelog WHERE overview = 'TESTOWY'
EXEC add_procedurelog @overview = 'TESTOWY', @date = '20180619 10:00:00 AM', @state = 0,
@prc_id = 1, @doctor_id = 2
SELECT * FROM procedurelog WHERE overview = 'TESTOWY'
GO
SELECT * FROM patient WHERE firstname = 'TEST_PACJENT'
EXEC add_patient6 @pesel = 99999, @firstname = 'TEST_PACJENT', @surname = 'TEST_PACJENT',
@room_id = 101, @doctor_id = 2, @prclg_id = 2
SELECT * FROM patient WHERE firstname = 'TEST_PACJENT'
GO

/*TESTING SEARCH AND UPDATE PROCEDURES*/
GO
SELECT * FROM certification WHERE id = 'cardio1'
EXEC sni_certification @id = 'cardio1', @overview = 'SNU_TEST'
SELECT * FROM certification WHERE id = 'cardio1'
GO
SELECT * FROM proceduretype WHERE id = 1
EXEC sni_proceduretype @id = 1, @overview = 'SNU_TEST', @personel = 5
SELECT * FROM proceduretype WHERE id = 1
GO
SELECT * FROM department WHERE id = 1
EXEC sni_department @dep_id = 1, @dep_name = 'SNU_TEST', @maxspace = 40, @freespace = 40
SELECT * FROM department WHERE id = 1
GO
SELECT * FROM room WHERE id = 1
EXEC sni_room1 @room_number = 1, @dep_id = 1, @maxspace = 33, @freespace = 33
SELECT * FROM room WHERE id = 1
GO
SELECT * FROM medicalpersonel WHERE firstname = 'TEST'
EXEC sni_medicalpersonel2 @firstname = 'TEST', @surname = 'TESTOWY', @dep_id = 1, @cert_id =
'uro1', @out_time = '20180619 10:00:00 AM'
SELECT * FROM medicalpersonel WHERE firstname = 'TEST'
GO
SELECT * FROM procedurelog WHERE overview = 'SNU_TEST'
EXEC sni_procedurelog @overview = 'SNU_TEST', @date = '20180619 10:00:00 AM', @state = 2,
@prc_id = 1, @doctor_id = 2, @id = 1
SELECT * FROM procedurelog WHERE overview = 'SNU_TEST'
GO
SELECT * FROM patient WHERE pesel = 99999
EXEC sni_patient @pesel = 99999, @room_id =1, @doctor_id = 3, @prclg_id = 1, @out_time =
'20181212 10:44:44 AM'
SELECT * FROM patient WHERE pesel = 99999
GO

/*TESTING MULTIPLE INSERT PROCEDURES*/
GO
SELECT *
FROM patient JOIN room
ON patient.room_id = room.id
WHERE pesel = 11111
EXEC add_patient_room1 @pesel = 11111, @firstname = 'TEST_SUPER', @surname = 'Kowalski',
@room_id = 2, @prclg_id = 1, @doc_surname = 'Blaszkowska', @max_space = 8, @dep_id = 1
SELECT *
FROM patient JOIN room
ON patient.room_id = room.id
WHERE pesel = 11111
GO
SELECT *
FROM medicalpersonel JOIN certification
ON medicalpersonel.certification_id = certification.id
WHERE firstname = 'TEST_SUPER1'
EXEC add_medicalpersonel_certification @firstname = 'TEST_SUPER1', @surname = 'Khalifa',
@dep_id = 1, @cert_id = 'gyne1', @cert_overview = 'TEST_SUPER1'
SELECT *
FROM medicalpersonel JOIN certification
ON medicalpersonel.certification_id = certification.id
WHERE firstname = 'TEST_SUPER1'
GO
SELECT *
FROM procedurelog JOIN proceduretype
ON procedurelog.procedure_id = proceduretype.id
WHERE procedurelog.overview = 'TEST_SUPER2'
EXEC add_procedurelog_procedure @overview = 'TEST_SUPER2', @date = '20180619 10:00:00 AM'
,@state = 0, @doctor_id = 4, @prc_oview = 'TEST_SUPER2', @doc_needed = 1
SELECT *
FROM procedurelog JOIN proceduretype
ON procedurelog.procedure_id = proceduretype.id
WHERE procedurelog.overview = 'TEST_SUPER2'
GO
