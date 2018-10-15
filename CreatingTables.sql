/*NEW TABLES*/
CREATE TABLE certification(
id NVARCHAR(50) PRIMARY KEY,
overview NVARCHAR(200)
)
CREATE TABLE proceduretype (
id INT IDENTITY(1,1) NOT NULL PRIMARY KEY,
overview NVARCHAR(300),
personel INT,
successrate FLOAT,
no_procedures INT
)
CREATE TABLE department (
id INT IDENTITY(1,1) NOT NULL PRIMARY KEY,
dep_name NVARCHAR(100),
free_space INT NOT NULL,
max_space INT NOT NULL
)
CREATE TABLE room (
id INT NOT NULL PRIMARY KEY,
free_space INT NOT NULL,
max_space INT NOT NULL,
department_id INT FOREIGN KEY REFERENCES department(id)
)
CREATE TABLE medicalpersonel (
id INT IDENTITY(1,1) NOT NULL PRIMARY KEY,
firstname NVARCHAR(100) NOT NULL,
surname NVARCHAR(150) NOT NULL,
inside DATETIME NOT NULL,
outside DATETIME,
department_id INT FOREIGN KEY REFERENCES department(id),
certification_id NVARCHAR(50) FOREIGN KEY REFERENCES certification(id)
)
CREATE TABLE procedurelog (
id INT IDENTITY(1,1) NOT NULL PRIMARY KEY,
overview NVARCHAR(300),
prc_date DATETIME,
prc_state INT,
procedure_id INT FOREIGN KEY REFERENCES proceduretype(id),
medical_personel_id INT FOREIGN KEY REFERENCES medicalpersonel(id)
)
CREATE TABLE patient (
pesel BIGINT PRIMARY KEY,
firstname NVARCHAR(100) NOT NULL,
surname NVARCHAR(150) NOT NULL,
inside DATETIME NOT NULL,
outside DATETIME,
room_id INT FOREIGN KEY REFERENCES room(id),
medical_personel_id INT FOREIGN KEY REFERENCES medicalpersonel(id),
procedurelog_id INT FOREIGN KEY REFERENCES procedurelog(id)
)