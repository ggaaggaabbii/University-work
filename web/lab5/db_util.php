<?php
class DBUtils {
	private $host = 'localhost';
  private $port = '8889';
	private $db   = 'mysql';
	private $user = 'Gabriel';
	private $pass = 'dQo4tj0DLatcrKn5';
	private $charset = 'utf8';

	private $pdo;
	private $error;

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

	public function select($type) {
		$stmt = $this->pdo->query("SELECT * FROM recipe WHERE type=$type");
		return $stmt->fetchAll(PDO::FETCH_ASSOC);
	}

	public function insert($author, $name, $type, $recipe) {
		$affected_rows = $this->pdo->exec("INSERT into recipe values('" . $author . "','" . $name ."', " . $type . ", '" . $recipe . "');");
		return $affected_rows;
	}

	public function delete ($name) {
		$affected_rows = $this->pdo->exec("DELETE from recipe where name=" . $name);
		return $affected_rows;
	}

	public function update ($name, $author, $type, $recipe) {
		$affected_rows = $this->pdo->exec("UPDATE recipe SET author='" . $author ."' where id=" . $id);

	}
}


?>
