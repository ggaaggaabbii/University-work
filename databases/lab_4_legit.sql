DROP PROC IF EXISTS uspInsertIngredient
GO

CREATE PROC uspInsertIngredient
AS
	INSERT INTO Ingredient (price, taste, name)
	VALUES (ABS(CHECKSUM(NEWID())), CONVERT(varchar(30), LEFT(NEWID(),30)), CONVERT(varchar(30), LEFT(NEWID(),30)))
GO

DROP PROC IF EXISTS uspInsertRecipe
GO

CREATE PROC uspInsertRecipe
AS
	INSERT INTO Recipe (original_country, is_vegan, price)
	VALUES (CONVERT(varchar(30), LEFT(NEWID(),30)), CAST(ROUND(RAND(),0) AS BIT), ABS(CHECKSUM(NEWID())))
GO

DROP PROC IF EXISTS uspInsertContains
GO

CREATE PROC uspInsertContains
AS
	DECLARE @rid INT
	DECLARE @iid INT
	DECLARE @go INT
	SELECT @go = 1

	WHILE @go = 1
	BEGIN
		SELECT TOP 1 @rid = rid FROM Recipe
		ORDER BY NEWID()

		SELECT @go = COUNT(*) 
		FROM Containing
		WHERE rid = @rid

	END
	SELECT TOP 1 @iid = iid FROM Ingredient
	ORDER BY NEWID()

	INSERT INTO Containing(rid, iid)
	VALUES(@rid, @iid)
GO

DROP PROC IF EXISTS uspInsertServes
GO

CREATE PROC uspInsertServes
AS
	DECLARE @rid INT
	DECLARE @reid INT
	DECLARE @go INT
	SELECT @go = 1

	WHILE @go = 1
	BEGIN
		SELECT TOP 1 @rid = rid FROM Recipe
		ORDER BY NEWID()

		SELECT @go = COUNT(*) 
		FROM Containing
		WHERE rid = @rid

	END
	SELECT TOP 1 @reid = rid FROM Restaurant
	ORDER BY NEWID()

	INSERT INTO Serves(rid, reid)
	VALUES(@rid, @reid)
GO

DROP PROC IF EXISTS uspInsertCity
GO

CREATE PROC uspInsertCity
AS
	INSERT INTO City (name, latitude, longitude)
	VALUES (CONVERT(char(30), LEFT(NEWID(),30)), ABS(CHECKSUM(NEWID())), ABS(CHECKSUM(NEWID())))
GO

DROP PROC IF EXISTS uspInsertHotel
GO

CREATE PROC uspInsertHotel
AS
	DECLARE @cityId INT

	SELECT TOP 1 @cityId = cid FROM City
	ORDER BY NEWID()

	INSERT INTO Hotel (address, cid, confort, name)
	VALUES (CONVERT(char(30), LEFT(NEWID(),30)), @cityId, ABS(CHECKSUM(NEWID())), CONVERT(char(30), LEFT(NEWID(),30)))
GO

DROP PROC IF EXISTS uspInsertRestaurant
GO

CREATE PROC uspInsertRestaurant
AS
	DECLARE @hotelId INT
	DECLARE @go INT
	SELECT @go = 1

	--get a unique hotel id
	WHILE @go = 1
	BEGIN
		SELECT TOP 1 @hotelId = hid FROM Hotel
		ORDER BY NEWID()

		SELECT @go = COUNT(*) 
		FROM Restaurant
		WHERE hid = @hotelId

	END

	INSERT INTO Restaurant (closing_hour, opening_hour, hid)
	VALUES(ABS(CHECKSUM(NEWID())), ABS(CHECKSUM(NEWID())), @hotelId)

GO

DROP VIEW IF EXISTS getCityNames
GO

CREATE VIEW getCityNames AS
SELECT DISTINCT name
FROM City
GO

DROP VIEW IF EXISTS getHotelNameForRestaurant
GO

CREATE VIEW getHotelNameForRestaurant AS
SELECT R.rid, H.name
FROM Restaurant R INNER JOIN Hotel H ON R.hid = H.hid
GO

DROP VIEW IF EXISTS getNrOfRestaurantsForCity
GO

CREATE VIEW getNrOfRestaurantsForCity AS
SELECT C.name, COUNT(R.rid) AS Nr
FROM City C INNER JOIN HOTEL H ON H.cid = C.cid
		INNER JOIN Restaurant R ON R.hid = H.hid
GROUP BY C.name
GO

DROP VIEW IF EXISTS getOriginalCountryForRecipe
GO

CREATE VIEW getOriginalCountryForRecipe AS
SELECT DISTINCT original_country
FROM Recipe
GO

DROP VIEW IF EXISTS getIngredientNameForRecipe
GO

CREATE VIEW getIngredientNameForRecipe AS
SELECT R.rid, I.name
FROM Recipe R INNER JOIN Containing C ON R.rid = C.rid
	INNER JOIN Ingredient I ON C.iid = I.iid
GO

DROP VIEW IF EXISTS getNrOfIngredientsForRecipe
GO

CREATE VIEW getNrOfIngredientsForRecipe AS
SELECT R.rid, COUNT(*) AS Nr
FROM Recipe R INNER JOIN Containing C ON R.rid = C.rid
	INNER JOIN Ingredient I ON C.iid = I.iid
GROUP BY R.rid
GO

DROP VIEW IF EXISTS getNrOfRecipesForCity
GO

CREATE VIEW getNrOfRecipesForCity AS
SELECT C.name, COUNT(*) AS Nr
FROM City C INNER JOIN HOTEL H ON H.cid = C.cid
		INNER JOIN Restaurant R ON R.hid = H.hid
		INNER JOIN Serves S ON S.reid = R.rid
		INNER JOIN Recipe Re ON S.rid = Re.rid
GROUP BY C.name
GO

DROP VIEW IF EXISTS getRecipePrice 
GO

CREATE VIEW getRecipePrice AS
SELECT R.price
FROM Recipe R
GO

DROP PROC IF EXISTS uspInsertAll
GO

CREATE PROC uspInsertAll
	@nrOfEntries INT,
	@insertFunc VARCHAR(30)
AS
	DECLARE @i INT
	SELECT @i = 0

	WHILE @i < @nrOfEntries
	BEGIN
		EXEC @insertFunc
		SELECT @i = @i + 1
	END
GO

DROP PROC IF EXISTS testRestaurantCity
GO

CREATE PROC testRestaurantCity
AS
	DECLARE @startTime DATETIME
	DECLARE @endTime DATETIME
	DECLARE @start DATETIME
	DECLARE @end DATETIME
	DECLARE @n INT
	DECLARE @testId INT
	DECLARE @tableId INT
	DECLARE @viewId INT
	DECLARE @testRunId INT

	SELECT @testId = 1
	SELECT @startTime = GETDATE()

	INSERT INTO TestRuns (Description, StartAt)
	VALUES ('testRestaurantCity', @startTime)

	-- Insert Values In Tables
	SELECT TOP 1 @testRunId = TestRunID
	FROM TestRuns
	ORDER BY TestRunID DESC

	-- Insert Cities
	PRINT 'Inserting In City'
	SELECT @start = GETDATE()
	SELECT @n = TT.NoOfRows, @tableId = T.TableID
	FROM TestTables TT INNER JOIN Tables T ON T.TableID = TT.TableID
			INNER JOIN Tests Te ON Te.TestID = TT.TestID
	WHERE T.Name = 'City' AND Te.TestID = 1
	EXEC uspInsertAll @n, 'uspInsertCity'
	SELECT @end = GETDATE()

	INSERT INTO TestRunTables (StartAt, EndAt, TestRunID, TableID)
	VALUES (@start, @end, @testRunId, @tableId)

	-- Insert Hotels
	PRINT 'Inserting In Hotel'
	SELECT @start = GETDATE()
	SELECT @n = TT.NoOfRows, @tableId = T.TableID
	FROM TestTables TT INNER JOIN Tables T ON T.TableID = TT.TableID
			INNER JOIN Tests Te ON Te.TestID = TT.TestID
	WHERE T.Name = 'Hotel' AND Te.TestID = 1
	EXEC uspInsertAll @n, 'uspInsertHotel'
	SELECT @end = GETDATE()

	INSERT INTO TestRunTables (StartAt, EndAt, TestRunID, TableID)
	VALUES (@start, @end, @testRunId, @tableId)

	-- Insert Restaurants
	PRINT 'Inserting In Restaurant'
	SELECT @start = GETDATE()
	SELECT @n = TT.NoOfRows, @tableId = T.TableID
	FROM TestTables TT INNER JOIN Tables T ON T.TableID = TT.TableID
			INNER JOIN Tests Te ON Te.TestID = TT.TestID
	WHERE T.Name = 'Restaurant' AND Te.TestID = 1
	EXEC uspInsertAll @n, 'uspInsertRestaurant'
	SELECT @end = GETDATE()

	INSERT INTO TestRunTables (StartAt, EndAt, TestRunID, TableID)
	VALUES (@start, @end, @testRunId, @tableId)

	-- Run Views for the test
	-- Run getCityNames
	PRINT 'Run In getCityNames'
	SELECT @start = GETDATE()
	SELECT @viewId = V.ViewID
	FROM Views V INNER JOIN TestViews TV ON V.ViewID = TV.ViewID
			INNER JOIN Tests T ON T.TestID = Tv.TestID
	WHERE V.Name = 'getCityNames'

	SELECT * FROM getCityNames
	SELECT @end = GETDATE()

	INSERT INTO TestRunViews (StartAt, EndAt, TestRunID, ViewID)
	VALUES (@start, @end, @testRunId, @viewId)

	-- Run getHotelNameForRestaurant
	PRINT 'Run In getHotelNameForRestaurant'
	SELECT @start = GETDATE()
	SELECT @viewId = V.ViewID
	FROM Views V INNER JOIN TestViews TV ON V.ViewID = TV.ViewID
			INNER JOIN Tests T ON T.TestID = Tv.TestID
	WHERE V.Name = 'getHotelNameForRestaurant'

	SELECT * FROM getHotelNameForRestaurant
	SELECT @end = GETDATE()

	INSERT INTO TestRunViews (StartAt, EndAt, TestRunID, ViewID)
	VALUES (@start, @end, @testRunId, @viewId)

	-- Run getNrOfRestaurantsForCity
	PRINT 'Run In getNrOfRestaurantsForCity'
	SELECT @start = GETDATE()
	SELECT @viewId = V.ViewID
	FROM Views V INNER JOIN TestViews TV ON V.ViewID = TV.ViewID
			INNER JOIN Tests T ON T.TestID = Tv.TestID
	WHERE V.Name = 'getNrOfRestaurantsForCity'

	SELECT * FROM getNrOfRestaurantsForCity
	SELECT @end = GETDATE()

	INSERT INTO TestRunViews (StartAt, EndAt, TestRunID, ViewID)
	VALUES (@start, @end, @testRunId, @viewId)

	-- Empty The Tables
	PRINT 'Cleaning Restaurant'
	DELETE FROM Restaurant
	PRINT 'Cleaning Hotel'
	DELETE FROM Hotel
	PRINT 'Cleaning City'
	DELETE FROM City

	SELECT @endTime = GETDATE()

	UPDATE TestRuns 
	SET EndAt = @endTime
	WHERE TestRunID = @testRunId
GO

DROP PROC IF EXISTS RunTest
GO

CREATE PROC RunTest
	@testId INT
AS
	DECLARE @testProc VARCHAR(30)

	SELECT @testProc = Name
	FROM Tests
	WHERE TestID = @testId

	EXEC @testProc
GO

DROP PROC IF EXISTS testRecipesWithIngredients
GO

CREATE PROC testRecipesWithIngredients
AS
	DECLARE @startTime DATETIME
	DECLARE @endTime DATETIME
	DECLARE @start DATETIME
	DECLARE @end DATETIME
	DECLARE @n INT
	DECLARE @testId INT
	DECLARE @tableId INT
	DECLARE @viewId INT
	DECLARE @testRunId INT

	SELECT @testId = 2
	SELECT @startTime = GETDATE()

	INSERT INTO TestRuns (Description, StartAt)
	VALUES ('testRecipesWithIngredients', @startTime)

	-- Insert Values In Tables
	SELECT TOP 1 @testRunId = TestRunID
	FROM TestRuns
	ORDER BY TestRunID DESC

	-- Insert Ingredient
	PRINT 'Inserting In Ingredient'
	SELECT @start = GETDATE()
	SELECT @n = TT.NoOfRows, @tableId = T.TableID
	FROM TestTables TT INNER JOIN Tables T ON T.TableID = TT.TableID
			INNER JOIN Tests Te ON Te.TestID = TT.TestID
	WHERE T.Name = 'Ingredient' AND Te.TestID = @testId
	EXEC uspInsertAll @n, 'uspInsertIngredient'
	SELECT @end = GETDATE()

	INSERT INTO TestRunTables (StartAt, EndAt, TestRunID, TableID)
	VALUES (@start, @end, @testRunId, @tableId)

	-- Insert Recipe
	PRINT 'Inserting In Recipe'
	SELECT @start = GETDATE()
	SELECT @n = TT.NoOfRows, @tableId = T.TableID
	FROM TestTables TT INNER JOIN Tables T ON T.TableID = TT.TableID
			INNER JOIN Tests Te ON Te.TestID = TT.TestID
	WHERE T.Name = 'Recipe' AND Te.TestID = @testId
	EXEC uspInsertAll @n, 'uspInsertRecipe'
	SELECT @end = GETDATE()

	INSERT INTO TestRunTables (StartAt, EndAt, TestRunID, TableID)
	VALUES (@start, @end, @testRunId, @tableId)

	-- Insert Containing
	PRINT 'Inserting In Containing'
	SELECT @start = GETDATE()
	SELECT @n = TT.NoOfRows, @tableId = T.TableID
	FROM TestTables TT INNER JOIN Tables T ON T.TableID = TT.TableID
			INNER JOIN Tests Te ON Te.TestID = TT.TestID
	WHERE T.Name = 'Containing' AND Te.TestID = @testId
	EXEC uspInsertAll @n, 'uspInsertContains'
	SELECT @end = GETDATE()

	INSERT INTO TestRunTables (StartAt, EndAt, TestRunID, TableID)
	VALUES (@start, @end, @testRunId, @tableId)

	-- Run Views for the test
	-- Run getOriginalCountryForRecipe
	PRINT 'Run In getOriginalCountryForRecipe'
	SELECT @start = GETDATE()
	SELECT @viewId = V.ViewID
	FROM Views V INNER JOIN TestViews TV ON V.ViewID = TV.ViewID
			INNER JOIN Tests T ON T.TestID = Tv.TestID
	WHERE V.Name = 'getOriginalCountryForRecipe'

	SELECT * FROM getOriginalCountryForRecipe
	SELECT @end = GETDATE()

	INSERT INTO TestRunViews (StartAt, EndAt, TestRunID, ViewID)
	VALUES (@start, @end, @testRunId, @viewId)

	-- Run getIngredientNameForRecipe
	PRINT 'Run In getIngredientNameForRecipe'
	SELECT @start = GETDATE()
	SELECT @viewId = V.ViewID
	FROM Views V INNER JOIN TestViews TV ON V.ViewID = TV.ViewID
			INNER JOIN Tests T ON T.TestID = Tv.TestID
	WHERE V.Name = 'getIngredientNameForRecipe'

	SELECT * FROM getIngredientNameForRecipe
	SELECT @end = GETDATE()

	INSERT INTO TestRunViews (StartAt, EndAt, TestRunID, ViewID)
	VALUES (@start, @end, @testRunId, @viewId)

	-- Run getNrOfIngredientsForRecipe
	PRINT 'Run In getNrOfIngredientsForRecipe'
	SELECT @start = GETDATE()
	SELECT @viewId = V.ViewID
	FROM Views V INNER JOIN TestViews TV ON V.ViewID = TV.ViewID
			INNER JOIN Tests T ON T.TestID = Tv.TestID
	WHERE V.Name = 'getNrOfIngredientsForRecipe'

	SELECT * FROM getNrOfIngredientsForRecipe
	SELECT @end = GETDATE()

	INSERT INTO TestRunViews (StartAt, EndAt, TestRunID, ViewID)
	VALUES (@start, @end, @testRunId, @viewId)

	-- Empty The Tables
	PRINT 'Cleaning Containing'
	DELETE FROM Containing
	PRINT 'Cleaning Ingredient'
	DELETE FROM Ingredient
	PRINT 'Cleaning Recipe'
	DELETE FROM Recipe

	SELECT @endTime = GETDATE()

	UPDATE TestRuns 
	SET EndAt = @endTime
	WHERE TestRunID = @testRunId
GO

DROP PROC IF EXISTS testRestaurantRecipe
GO

CREATE PROC testRestaurantRecipe
AS
	DECLARE @startTime DATETIME
	DECLARE @endTime DATETIME
	DECLARE @start DATETIME
	DECLARE @end DATETIME
	DECLARE @n INT
	DECLARE @testId INT
	DECLARE @tableId INT
	DECLARE @viewId INT
	DECLARE @testRunId INT

	SELECT @testId = 3
	SELECT @startTime = GETDATE()

	INSERT INTO TestRuns (Description, StartAt)
	VALUES ('testRecipesWithIngredients', @startTime)

	-- Insert Values In Tables
	SELECT TOP 1 @testRunId = TestRunID
	FROM TestRuns
	ORDER BY TestRunID DESC

	-- Insert Cities
	PRINT 'Inserting In City'
	SELECT @start = GETDATE()
	SELECT @n = TT.NoOfRows, @tableId = T.TableID
	FROM TestTables TT INNER JOIN Tables T ON T.TableID = TT.TableID
			INNER JOIN Tests Te ON Te.TestID = TT.TestID
	WHERE T.Name = 'City' AND Te.TestID = @testId
	EXEC uspInsertAll @n, 'uspInsertCity'
	SELECT @end = GETDATE()

	INSERT INTO TestRunTables (StartAt, EndAt, TestRunID, TableID)
	VALUES (@start, @end, @testRunId, @tableId)

	-- Insert Hotels
	PRINT 'Inserting In Hotel'
	SELECT @start = GETDATE()
	SELECT @n = TT.NoOfRows, @tableId = T.TableID
	FROM TestTables TT INNER JOIN Tables T ON T.TableID = TT.TableID
			INNER JOIN Tests Te ON Te.TestID = TT.TestID
	WHERE T.Name = 'Hotel' AND Te.TestID = @testId
	EXEC uspInsertAll @n, 'uspInsertHotel'
	SELECT @end = GETDATE()

	INSERT INTO TestRunTables (StartAt, EndAt, TestRunID, TableID)
	VALUES (@start, @end, @testRunId, @tableId)

	-- Insert Restaurants
	PRINT 'Inserting In Restaurant'
	SELECT @start = GETDATE()
	SELECT @n = TT.NoOfRows, @tableId = T.TableID
	FROM TestTables TT INNER JOIN Tables T ON T.TableID = TT.TableID
			INNER JOIN Tests Te ON Te.TestID = TT.TestID
	WHERE T.Name = 'Restaurant' AND Te.TestID = @testId
	EXEC uspInsertAll @n, 'uspInsertRestaurant'
	SELECT @end = GETDATE()

	INSERT INTO TestRunTables (StartAt, EndAt, TestRunID, TableID)
	VALUES (@start, @end, @testRunId, @tableId)

	-- Insert Recipe
	PRINT 'Inserting In Recipe'
	SELECT @start = GETDATE()
	SELECT @n = TT.NoOfRows, @tableId = T.TableID
	FROM TestTables TT INNER JOIN Tables T ON T.TableID = TT.TableID
			INNER JOIN Tests Te ON Te.TestID = TT.TestID
	WHERE T.Name = 'Recipe' AND Te.TestID = @testId
	EXEC uspInsertAll @n, 'uspInsertRecipe'
	SELECT @end = GETDATE()

	INSERT INTO TestRunTables (StartAt, EndAt, TestRunID, TableID)
	VALUES (@start, @end, @testRunId, @tableId)

	-- Insert Serves
	PRINT 'Inserting In Serves'
	SELECT @start = GETDATE()
	SELECT @n = TT.NoOfRows, @tableId = T.TableID
	FROM TestTables TT INNER JOIN Tables T ON T.TableID = TT.TableID
			INNER JOIN Tests Te ON Te.TestID = TT.TestID
	WHERE T.Name = 'Serves' AND Te.TestID = @testId
	EXEC uspInsertAll @n, 'uspInsertServes'
	SELECT @end = GETDATE()

	INSERT INTO TestRunTables (StartAt, EndAt, TestRunID, TableID)
	VALUES (@start, @end, @testRunId, @tableId)


	-- Run Views for the test
	-- Run getNrOfRestaurantsForCity
	PRINT 'Run In getNrOfRestaurantsForCity'
	SELECT @start = GETDATE()
	SELECT @viewId = V.ViewID
	FROM Views V INNER JOIN TestViews TV ON V.ViewID = TV.ViewID
			INNER JOIN Tests T ON T.TestID = Tv.TestID
	WHERE V.Name = 'getNrOfRestaurantsForCity'

	SELECT * FROM getNrOfRestaurantsForCity
	SELECT @end = GETDATE()

	INSERT INTO TestRunViews (StartAt, EndAt, TestRunID, ViewID)
	VALUES (@start, @end, @testRunId, @viewId)

	-- Run getNrOfRecipesForCity
	PRINT 'Run In getNrOfRecipesForCity'
	SELECT @start = GETDATE()
	SELECT @viewId = V.ViewID
	FROM Views V INNER JOIN TestViews TV ON V.ViewID = TV.ViewID
			INNER JOIN Tests T ON T.TestID = Tv.TestID
	WHERE V.Name = 'getNrOfRecipesForCity'

	SELECT * FROM getNrOfRecipesForCity
	SELECT @end = GETDATE()

	INSERT INTO TestRunViews (StartAt, EndAt, TestRunID, ViewID)
	VALUES (@start, @end, @testRunId, @viewId)

	-- Run getRecipePrice
	PRINT 'Run In getRecipePrice'
	SELECT @start = GETDATE()
	SELECT @viewId = V.ViewID
	FROM Views V INNER JOIN TestViews TV ON V.ViewID = TV.ViewID
			INNER JOIN Tests T ON T.TestID = Tv.TestID
	WHERE V.Name = 'getRecipePrice'

	SELECT * FROM getRecipePrice
	SELECT @end = GETDATE()

	INSERT INTO TestRunViews (StartAt, EndAt, TestRunID, ViewID)
	VALUES (@start, @end, @testRunId, @viewId)

	-- Empty The Tables
	PRINT 'Cleaning Serves'
	DELETE FROM Serves
	PRINT 'Cleaning Restaurant'
	DELETE FROM Restaurant
	PRINT 'Cleaning Hotel'
	DELETE FROM Hotel
	PRINT 'Cleaning City'
	DELETE FROM City
	PRINT 'Cleaning Recipe'
	DELETE FROM Recipe

	SELECT @endTime = GETDATE()

	UPDATE TestRuns 
	SET EndAt = @endTime
	WHERE TestRunID = @testRunId
GO

EXEC RunTest 3

SELECT * FROM TestRuns
SELECT * FROM TestRunTables