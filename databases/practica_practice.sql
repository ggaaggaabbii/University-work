DROP TABLE IF EXISTS RoutStation
DROP TABLE IF EXISTS Stations
DROP TABLE IF EXISTS Routs
DROP TABLE IF EXISTS Train
DROP TABLE IF EXISTS TrainTypes


CREATE TABLE TrainTypes(
	ttid TINYINT PRIMARY KEY IDENTITY(1, 1),
	descr VARCHAR(3000)
)

CREATE TABLE Train(
	tid TINYINT PRIMARY KEY IDENTITY(1, 1),
	name VARCHAR(3000),
	ttid TINYINT REFERENCES TrainTypes(ttid)
)

CREATE TABLE Routs(
	rid TINYINT PRIMARY KEY IDENTITY(1, 1),
	name VARCHAR(1000) UNIQUE,
	tid TINYINT REFERENCES Train(tid)
)

CREATE TABLE Stations(
	sid TINYINT PRIMARY KEY IDENTITY(1, 1),
	name VARCHAR(1000) UNIQUE
)

CREATE TABLE RoutStation(
	rid TINYINT REFERENCES Routs(rid) ,
	sid TINYINT REFERENCES Stations(sid),
	PRIMARY KEY (rid, sid),
	arrival TIME,
	departure TIME
)

GO

INSERT TrainTypes VALUES ('regio'), ('interregio')
INSERT Train VALUES ('t1', 1), ('t2', 2), ('t3', 2)
INSERT Routs VALUES ('r1', 1), ('r2', 2), ('r3', 3)
INSERT Stations VALUES ('s1'), ('s2'), ('s3')
INSERT RoutStation (rid, sid, arrival, departure) VALUES
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
	ELSE IF EXISTS (SELECT * FROM RoutStation WHERE rid = @RID AND sid = @SID)
		RAISERROR ('station already exists', 16, 1)
	ELSE
		INSERT RoutStation(rid, sid, arrival, departure) VALUES (@RID, @SID, @Arrival, @Departure)
GO



uspStationRout 'r3', 's2','19:10', '12:10' 
SELECT * FROM RoutStation

GO 

CREATE OR ALTER VIEW vRSt AS
SELECT name 
FROM Routs R
WHERE NOT EXISTS
	(SELECT sid
	FROM Stations
	EXCEPT
	SELECT sid
	FROM RoutStation
	WHERE rid = R.rid)

GO

SELECT * FROM vRSt

GO
CREATE OR ALTER FUNCTION ufGetStationsByNrRouts (@r INT)
RETURNS TABLE
RETURN
SELECT S.name
FROM Stations S
WHERE S.sid IN (SELECT sid
				FROM RoutStation
				GROUP BY sid
				HAVING COUNT(*) > @r)
GO

SELECT *
FROM ufGetStationsByNrRouts (3)