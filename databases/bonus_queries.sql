--Employees that work in multiple hotels and can come in contact 
--with Henrik Sebok (work in the same hotel), 
--but are not named Vasile
SELECT DISTINCT E.name, E.hotel
FROM (SELECT E1.name AS name, E1.hotel
	  FROM (SELECT H.hid AS hid, H.name AS hotel, E2.name AS name
			FROM Hotel H
			INNER JOIN Employs Ep ON H.hid = Ep.hid
			INNER JOIN Employee E2 ON E2.eid = Ep.eid
			WHERE EXISTS (SELECT *
						  FROM Chef C, Restaurant R
						  WHERE C.rid = R.rid AND R.hid = H.hid AND C.name = 'Henrik Sebok')
			) AS E1
	  ) AS E
WHERE E.name NOT LIKE '%Vasile%' AND E.name IN (SELECT E3.name
												FROM Employee E3
												WHERE EXISTS (SELECT Emp.eid, COUNT(*) as Co
															  FROM Employs Emp
														      WHERE E3.eid = Emp.eid
															  GROUP BY Emp.eid
															  HAVING 2 <= COUNT(*)
															))


GO

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

GO

--Hotels with more employees than a Hotel Paradis
SELECT H.hid, H.name
FROM Hotel H
WHERE dbo.ufnGetNumberOfEmployees(hid) > ANY(SELECT dbo.ufnGetNumberOfEmployees(hid) as number
											 FROM Hotel H
											 WHERE H.name LIKE '%Paradis%')

