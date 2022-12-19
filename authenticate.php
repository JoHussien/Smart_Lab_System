<?php

if(isset($_GET["id"])) {
   $id = $_GET["id"]; // get temperature value from HTTP GET

   $servername = "db4free.net";
   $username = "seifeldin";
   $password = "aucauth1234";
   $database_name = "lab_auth";

   // Create MySQL connection fom PHP to MySQL server
   $connection = new mysqli($servername, $username, $password, $database_name);
   // Check connection
   if ($connection->connect_error) {
      die("MySQL connection failed: " . $connection->connect_error);
   } else {
      echo "MySQL connections succeeded";
   }

   $sql = "INSERT INTO user (user_id, password) VALUES ($id, '1234')";

   if ($connection->query($sql) === TRUE) {
      echo "New record created successfully";
   } else {
      echo "Error: " . $sql . " => " . $connection->error;
   }

   $connection->close();
} else {
   echo "ID is not set in the HTTP request";
}
?>