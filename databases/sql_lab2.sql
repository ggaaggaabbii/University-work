IF OBJECT_ID('Bed', 'U') IS NOT NULL
	DROP TABLE Bed

IF OBJECT_ID('Tv', 'U') IS NOT NULL
	DROP TABLE Tv

IF OBJECT_ID('Bathroom', 'U') IS NOT NULL
	DROP TABLE Bathroom

IF OBJECT_ID('Room', 'U') IS NOT NULL
	DROP TABLE Room

IF OBJECT_ID('Employs', 'U') IS NOT NULL
	DROP TABLE Employs

IF OBJECT_ID('Employee', 'U') IS NOT NULL
	DROP TABLE Employee

IF OBJECT_ID('Chef', 'U') IS NOT NULL
	DROP TABLE Chef

IF OBJECT_ID('Serves', 'U') IS NOT NULL
	DROP TABLE Serves

IF OBJECT_ID('Containing', 'U') IS NOT NULL
	DROP TABLE Containing

IF OBJECT_ID('Recipe', 'U') IS NOT NULL
	DROP TABLE Recipe

IF OBJECT_ID('Ingredient', 'U') IS NOT NULL
	DROP TABLE Ingredient

IF OBJECT_ID('Restaurant', 'U') IS NOT NULL
	DROP TABLE Restaurant

IF OBJECT_ID('Hotel', 'U') IS NOT NULL
	DROP TABLE Hotel

IF OBJECT_ID('City', 'U') IS NOT NULL
	DROP TABLE City

CREATE TABLE City(
	cid INT PRIMARY KEY IDENTITY(1, 1),
	name CHAR(30),
	latitude FLOAT,
	longitude FLOAT
)

CREATE TABLE Hotel(
	hid INT PRIMARY KEY IDENTITY(1, 1),
	name CHAR(30),
	address CHAR(30),
	confort INT,
	cid INT REFERENCES City(cid)
)

CREATE TABLE Employee(
	eid INT PRIMARY KEY IDENTITY(1, 1),
	name CHAR(30),
	salary INT
)

CREATE TABLE Employs(
	eid INT REFERENCES Employee(eid),
	hid INT REFERENCES Hotel(hid),
	PRIMARY KEY(eid, hid)
)

CREATE TABLE Room(
	rid INT PRIMARY KEY IDENTITY(1, 1),
	number INT,
	floor INT,
	hid INT REFERENCES Hotel(hid)
)

CREATE TABLE Tv(
	tid INT PRIMARY KEY IDENTITY(1, 1),
	distance INT,
	resolution VARCHAR(15),
	rid INT REFERENCES Room(rid)
)

CREATE TABLE Bed(
	bid INT PRIMARY KEY IDENTITY(1, 1),
	size INT,
	confort_level INT,
	rid INT REFERENCES Room(rid)
)

CREATE TABLE Bathroom(
	bid INT PRIMARY KEY IDENTITY(1, 1),
	has_jacuzzi BIT,
	rid INT REFERENCES Room(rid)
)

CREATE TABLE Restaurant(
	rid INT PRIMARY KEY IDENTITY(1, 1),
	hid INT UNIQUE NOT NULL,
	opening_hour INT,
	closing_hour INT,
)

ALTER TABLE Restaurant
ADD CONSTRAINT FK_Restaurant_Hotel FOREIGN KEY(hid)
	REFERENCES Hotel(hid)

CREATE TABLE Chef(
	cid INT PRIMARY KEY IDENTITY(1, 1),
	name VARCHAR(60),
	stars INT,
	rid INT REFERENCES Restaurant(rid)
)

CREATE TABLE Recipe(
	rid INT PRIMARY KEY IDENTITY(1, 1),
	is_vegan BIT,
	original_country VARCHAR(30),
	price INT
)

CREATE TABLE Serves(
	rid INT REFERENCES Recipe(rid),
	reid INT REFERENCES Restaurant(rid),
	PRIMARY KEY(rid, reid)
)

CREATE TABLE Ingredient(
	iid INT PRIMARY KEY IDENTITY(1, 1),
	price INT,
	taste VARCHAR(30),
	name CHAR(30)
)

CREATE TABLE Containing(
	iid INT REFERENCES Ingredient(iid),
	rid INT REFERENCES Recipe(rid),
	PRIMARY KEY(iid, rid)
)

IF OBJECT_ID (N'dbo.ufnGetNumberOfEmployees', N'FN') IS NOT NULL  
    DROP FUNCTION ufnGetNumberOfEmployees;  
GO  
CREATE FUNCTION dbo.ufnGetNumberOfEmployees(@HotelID int)  
RETURNS int   
AS   
-- Returns number of employees in a hotel  
BEGIN  
    DECLARE @ret int;  
    SELECT @ret = SUM(H.Count)   
    FROM (SELECT COUNT(*) AS Count
		  FROM Employs E
		  WHERE E.hid = @HotelID) AS H
     IF (@ret IS NULL)   
        SET @ret = 0;  
    RETURN @ret;  
END;
