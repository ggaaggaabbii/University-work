-- SELECT * FROM Chef -- Ctrl + L to see the exec plan
-- EXEC sp_helpindex Chef

DROP TABLE IF EXISTS Tc
DROP TABLE IF EXISTS Tb
DROP TABLE IF EXISTS Ta

CREATE TABLE Ta(
	aid INT PRIMARY KEY,
	a2 INT UNIQUE,
	name VARCHAR(30)
)

CREATE TABLE Tb(
	bid INT PRIMARY KEY,
	b2 INT
)

CREATE TABLE tc(
	cid INT PRIMARY KEY,
	aid INT REFERENCES Ta(aid),
	bid INT REFERENCES Tb(bid)
)


-- a
-- Clustered Index Scan
SELECT *
FROM Ta
ORDER BY aid

-- Clustered Index Seek
SELECT aid
FROM Ta
WHERE aid < 50

-- Nonclustered Index Scan
SELECT a2
FROM Ta
ORDER BY a2

-- Nonclustered Index Seek
SELECT *
FROM Ta
WHERE a2 < 50

-- Nonclustered Index Seek + Key lookup
SELECT name
FROM Ta
WHERE a2 = 4

-- b
-- before: Clustered Index Scan
-- after: Nonclustered Index Seek
SELECT *
FROM Tb
WHERE b2 = 2

CREATE NONCLUSTERED 
	INDEX Tb_index
ON Tb(b2)

GO
-- c
-- Nonclustered Index Seek on B
-- Clustered Index Seek on C
-- Clustered Index Seek on A
CREATE VIEW v AS
SELECT A.aid, B.b2
FROM  Ta A INNER JOIN Tc C ON A.aid = C.aid INNER JOIN Tb B ON B.bid = C.cid
WHERE A.aid < 50 AND C.bid > 10 AND B.b2 < 3
GO

SELECT * FROM v