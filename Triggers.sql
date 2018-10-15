/*CREATE TRIGGERS*/
GO
CREATE TRIGGER patient_show_room ON patient FOR UPDATE
AS
SELECT i.firstname, i.surname, i.room_id FROM inserted i
WHERE NOT EXISTS (SELECT * FROM inserted i JOIN deleted d ON i.room_id = d.room_id)
GO
CREATE TRIGGER del_patient ON patient FOR DELETE
AS
BEGIN TRAN T1
IF EXISTS(SELECT * FROM deleted d
WHERE d.outside is null)
BEGIN
RAISERROR('nie wolno zmieniac outside gdy jest nullem', 16, 3)
ROLLBACK TRAN
END
GO
CREATE TRIGGER procedure_update ON procedurelog FOR UPDATE
AS
UPDATE proceduretype
SET no_procedures = no_procedures+1
WHERE id IN (SELECT d.procedure_id FROM deleted d JOIN
inserted i ON d.id = i.id JOIN
proceduretype p ON i.procedure_id = p.id)
UPDATE proceduretype
SET successrate = successrate+ 5.0
WHERE id IN (SELECT d.procedure_id FROM deleted d JOIN
inserted i ON d.id = i.id JOIN
proceduretype p ON i.procedure_id = p.id)
GO
CREATE TRIGGER room_show_dep ON room FOR UPDATE
AS
SELECT i.department_id FROM inserted i
WHERE NOT EXISTS (SELECT i.id FROM inserted i JOIN deleted d ON i.department_id =
d.department_id)
GO
CREATE TRIGGER patient_leave ON patient FOR UPDATE
AS
UPDATE procedurelog
SET prc_date = NULL, prc_state = 0
WHERE id IN (SELECT p.id FROM inserted i JOIN procedurelog p ON p.id = i.procedurelog_id)
GO
CREATE TRIGGER del_room ON room FOR DELETE
AS
SELECT d.department_id FROM deleted d
GO
CREATE TRIGGER doc_leave ON medicalpersonel FOR UPDATE
AS
SELECT * FROM procedurelog
WHERE id IN (SELECT pl.id FROM inserted i JOIN
procedurelog pl ON i.id = pl.medical_personel_id WHERE i.outside
IS NOT NULL)
GO
CREATE TRIGGER add_personel ON medicalpersonel FOR INSERT
AS
SELECT c.overview FROM inserted i JOIN
certification c ON c.id = i.certification_id
GO
CREATE TRIGGER insert_prclg ON procedurelog FOR INSERT
AS
SELECT * FROM proceduretype
WHERE id IN (SELECT p.id FROM inserted i JOIN proceduretype p ON p.id = i.procedure_id)

/*TESTING TRIGGERS*/
UPDATE patient
SET room_id = 999
WHERE pesel = 99999
GO
DELETE FROM patient WHERE firstname = 'Lisa'
GO
SELECT * FROM procedurelog pl JOIN proceduretype p ON pl.procedure_id = p.id
UPDATE procedurelog
SET prc_state = 2
WHERE id = 1
SELECT * FROM procedurelog pl JOIN proceduretype p ON pl.procedure_id = p.id
GO
UPDATE room
SET department_id = 4
WHERE id = 101
GO
SELECT * FROM procedurelog pl JOIN patient p ON p.procedurelog_id = pl.id WHERE p.pesel = 123
UPDATE patient
SET outside = '20180619 10:00:00 AM'
WHERE pesel = 123
SELECT * FROM procedurelog pl JOIN patient p ON p.procedurelog_id = pl.id WHERE p.pesel =
123
GO
DELETE room
WHERE id = 501
GO
UPDATE medicalpersonel
SET outside = '20180619 10:00:00 AM'
WHERE id = 3
GO
INSERT INTO medicalpersonel
VALUES('KOWAL','KOWALSKI', GETDATE(), NULL, 3, 'endo1')
GO
INSERT INTO procedurelog
VALUES('TEST_ZABIEG','20180619 10:00:00 AM',0,1,4)
GO