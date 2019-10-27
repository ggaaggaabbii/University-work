<?php
class DBUtils {
	private $host = 'localhost';
  private $port = '8889';
	private $db   = 'conference';
	private $user = 'Gabriel';
	private $pass = 'dQo4tj0DLatcrKn5';
	private $charset = 'utf8';

	private $pdo;
	private $error;
	private $deleteStmt;

	public function __construct () {
		$dsn = "mysql:host=$this->host;port=$this->port;dbname=$this->db;charset=$this->charset";
		$opt = array(PDO::ATTR_ERRMODE => PDO::ERRMODE_EXCEPTION,
			PDO::ATTR_DEFAULT_FETCH_MODE => PDO::FETCH_ASSOC,
			PDO::ATTR_EMULATE_PREPARES => false);
		try {
			$this->pdo = new PDO($dsn, $this->user, $this->pass, $opt);
		} // Catch any errors
		catch(PDOException $e){
			$this->error = $e->getMessage();
			echo "Error connecting to DB: " . $this->error;
		}
	}

	public function selectFlights() {
		$stmt = $this->pdo->query("SELECT * FROM Flights");
		return $stmt->fetchAll(PDO::FETCH_ASSOC);
	}

	public function filter($name) {
		$stmt = $this->pdo->query("SELECT * FROM recipe WHERE name='$name'");
		return $stmt->fetchAll(PDO::FETCH_ASSOC);
	}

	public function insert($author, $name, $type, $recipe) {
		try {
			$stmt = $this->pdo->prepare("INSERT INTO recipe VALUES(:author, :name, :type, :recipe);");
    	$stmt->bindParam(':author', $author);
			$stmt->bindParam(':name', $name);
			$stmt->bindParam(':type', $type);
			$stmt->bindParam(':recipe', $recipe);
			$stmt->execute();
			return "ok";
		}catch(PDOException $e){
			return "error...";
	  }
	}

	public function reserveFlight ($name, $flightId) {
		try {
			$stmt = $this->pdo->prepare("UPDATE Flights SET Seats=Seats-1 WHERE ID=:id");
			$stmt->bindParam(':id', $flightId);
			$stmt->execute();
			return "ok";
		}catch(PDOException $e){
			return "error...";
		}
		try {
			$resId = rand();
			$stmt = $this->pdo->prepare("INSERT INTO FlightReservations VALUES(:id, :flightId, :client);");
    	$stmt->bindParam(':id', $resId);
			$stmt->bindParam(':flightId', $flightId);
			$stmt->bindParam(':client', $name);
			$stmt->execute();
			return "ok";
		}catch(PDOException $e){
			return "error...";
	  }

		$stmt = $this->pdo->query("SELECT * FROM Hotels");
		return $stmt->fetchAll(PDO::FETCH_ASSOC);
	}

	public function update ($id, $author, $name, $type, $recipe) {
		try {
			$stmt = $this->pdo->prepare("UPDATE recipe SET author=:author, name=:name, type=:type, recipe=:recipe WHERE name=:id");
			$stmt->bindParam(':author', $author);
			$stmt->bindParam(':name', $name);
			$stmt->bindParam(':type', $type);
			$stmt->bindParam(':recipe', $recipe);
			$stmt->bindParam(':id', $id);
			$stmt->execute();
			return "ok";
		}catch(PDOException $e){
			return "error...";
		}
	}
}


?>
