DROP TABLE IF EXISTS RS
DROP TABLE IF EXISTS Routs
DROP TABLE IF EXISTS Stations
DROP TABLE IF EXISTS Trains
DROP TABLe IF EXISTS TT

CREATE TABLE TT(
	ttid INT PRIMARY KEY IDENTITY (1, 1),
	descr VARCHAR(30)
)

CREATE TABLE Trains(
	tid INT PRIMARY KEY IDENTITY(1, 1),
	name VARCHAR(30),
	type INT REFERENCES TT(ttid)
)

CREATE TABLE Routs (
	rid INT PRIMARY KEY IDENTITY(1, 1),
	tid INT REFERENCES Trains(tid),
	name VARCHAR(30) UNIQUE
)

CREATE TABLE Stations (
	sid INT PRIMARY KEY IDENTITY(1, 1),
	name VARCHAR(30) UNIQUE
)

CREATE TABLE RS(
	sid INT REFERENCES Stations(sid),
	rid INT REFERENCES Routs(rid),
	PRIMARY KEY (sid, rid),
	arDate TIME,
	depDate TIME
)


GO 

INSERT TT VALUES ('regio'), ('interregio')
INSERT Trains VALUES ('t1', 1), ('t2', 2), ('t3', 2)
INSERT Routs (name, tid) VALUES ('r1', 1), ('r2', 2), ('r3', 3)
INSERT Stations VALUES ('s1'), ('s2'), ('s3')
INSERT RS (rid, sid, arDate, depDate) VALUES
		 (1, 1, '6:00', '6:10'),
		 (1, 2, '6:00', '6:10'),		
		 (1, 3, '6:00', '6:10'),
		 (2, 1, '6:00', '6:10'),
		 (2, 2, '6:00', '6:10'),
		 (2, 3, '6:00', '6:10'),
		 (3, 1, '6:00', '6:10')

GO

CREATE OR ALTER PROC uspStationRout @RName VARCHAR(1000), @SName VARCHAR(1000), @Arrival TIME, @Departure TIME
AS
	DECLARE @RID TINYINT = (SELECT rid FROM Routs WHERE name = @RName),
			@SID TINYINT = (SELECT sid FROM Stations WHERE name = @SName)


	IF @RID IS NULL OR @SID IS NULL
		RAISERROR ('route/station don''t exist', 16, 1)
	ELSE IF EXISTS (SELECT * FROM RS WHERE rid = @RID AND sid = @SID)
		RAISERROR ('station already exists', 16, 1)
	ELSE
		INSERT RS(rid, sid, arDate, depDate) VALUES (@RID, @SID, @Arrival, @Departure)
GO

uspStationRout 'r3', 's2','19:10', '12:10' 
SELECT * FROM RS

