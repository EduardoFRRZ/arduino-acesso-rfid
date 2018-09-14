<?php
	
	include("conexao.php");
	$consulta = "select * from funcionarios";
	$con = $mysqli->query($consulta) or die($mysqli->error);
	
?>