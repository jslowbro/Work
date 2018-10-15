/* INSERT PROCEDURES*/
CREATE PROCEDURE add_certification @id nvarchar(50), @overview nvarchar(200)
AS
INSERT INTO certification
VALUES(@id, @overview)
GO
CREATE PROCEDURE add_proceduretype @overview nvarchar(300), @personel int
AS
INSERT INTO proceduretype
VALUES(@overview, @personel, 0.0, 0)
GO
CREATE PROCEDURE add_department1 @dep_name nvarchar(100)
AS
INSERT INTO department
VALUES(@dep_name,0 , 0)
GO
CREATE PROCEDURE add_room2 @room_number int, @dep_id int, @maxspace int
AS
UPDATE department
SET max_space = max_space + @maxspace, free_space = free_space + @maxspace
WHERE id = @dep_id
INSERT INTO room
VALUES(@room_number,@maxspace,@maxspace,@dep_id)
GO
CREATE PROCEDURE add_medicalpersonel @firstname NVARCHAR(100), @surname NVARCHAR(150),
@dep_id int, @cert_id nvarchar(50)
AS
INSERT INTO medicalpersonel
VALUES(@firstname,@surname,GETDATE(), NULL, @dep_id, @cert_id)
GO
CREATE PROCEDURE add_procedurelog @overview NVARCHAR(300), @date DATETIME ,@state int,
@prc_id int, @doctor_id int
AS
INSERT INTO procedurelog
VALUES(@overview,@date,@state,@prc_id,@doctor_id)
GO
CREATE PROCEDURE add_patient6 @pesel bigint, @firstname NVARCHAR(100), @surname
NVARCHAR(150), @room_id int, @doctor_id int, @prclg_id int
AS
INSERT INTO patient
VALUES(@pesel,@firstname,@surname,GETDATE(), NULL, @room_id, @doctor_id,@prclg_id)
UPDATE room
SET free_space = free_space-1
WHERE id = @room_id
GO

/*SEARCH AND UPDATE PROCEDURES*/
CREATE PROCEDURE sni_certification @id nvarchar(50), @overview nvarchar(200)
AS
UPDATE certification
SET overview = @overview
WHERE id = @id
GO
CREATE PROCEDURE sni_proceduretype @id int, @overview nvarchar(300), @personel int
AS
UPDATE proceduretype
SET overview = @overview, personel = @personel
WHERE id = @id
GO
CREATE PROCEDURE sni_department @dep_id int, @dep_name nvarchar(100), @maxspace int,
@freespace int
AS
UPDATE department
SET dep_name = @dep_name, max_space = @maxspace, free_space = @freespace
WHERE id = @dep_id
GO
CREATE PROCEDURE sni_room1 @room_number int, @dep_id int, @maxspace int, @freespace int
AS
UPDATE room
SET department_id = @dep_id, max_space = @maxspace, free_space = @freespace
WHERE @room_number = id
GO
CREATE PROCEDURE sni_medicalpersonel2 @firstname NVARCHAR(100), @surname NVARCHAR(150),
@dep_id int, @cert_id nvarchar(50), @out_time datetime
AS
UPDATE medicalpersonel
SET department_id = @dep_id, certification_id = @cert_id, outside = @out_time
WHERE firstname = @firstname AND surname = @surname
GO
CREATE PROCEDURE sni_procedurelog @overview NVARCHAR(300), @date DATETIME ,@state int,
@prc_id int, @doctor_id int, @id int
AS
UPDATE procedurelog
SET overview = @overview,prc_date = @date,prc_state = @state, procedure_id =
@prc_id,medical_personel_id = @doctor_id
WHERE id = @id
GO
CREATE PROCEDURE sni_patient @pesel bigint, @room_id int, @doctor_id int, @prclg_id int,
@out_time datetime
AS
UPDATE patient
SET room_id = @room_id, medical_personel_id = @doctor_id, procedurelog_id = @prclg_id,
outside = @out_time
WHERE @pesel = pesel
GO

/*MULTIPLE INSERT PROCEDURES*/
CREATE PROCEDURE add_patient_room1 @pesel bigint, @firstname NVARCHAR(100), @surname
NVARCHAR(150), @room_id int, @prclg_id int, @doc_surname NVARCHAR(150), @max_space int,
@dep_id int
AS
DECLARE @doc_id int
SET @doc_id = (SELECT id FROM medicalpersonel
WHERE surname = @doc_surname)
INSERT INTO room
VALUES(@room_id, (@max_space - 1), @max_space, @dep_id)
INSERT INTO patient
VALUES(@pesel,@firstname,@surname,GETDATE(), NULL, @room_id, @doc_id,@prclg_id)
GO
CREATE PROCEDURE add_medicalpersonel_certification @firstname NVARCHAR(100), @surname
NVARCHAR(150), @dep_id int, @cert_id nvarchar(50), @cert_overview nvarchar(200)
AS
INSERT INTO certification
VALUES(@cert_id,@cert_overview)
INSERT INTO medicalpersonel
VALUES(@firstname,@surname,GETDATE(), NULL, @dep_id, @cert_id)
GO
CREATE PROCEDURE add_procedurelog_procedure @overview NVARCHAR(300), @date DATETIME ,@state
int, @doctor_id int, @prc_oview nvarchar(300), @doc_needed int
AS
INSERT INTO proceduretype
VALUES(@prc_oview, @doc_needed, 0.0, 0)
DECLARE @prc_id int
SET @prc_id = (SELECT MAX(p.id)
FROM proceduretype AS p)
INSERT INTO procedurelog
VALUES(@overview,@date,@state,@prc_id,@doctor_id)
GO