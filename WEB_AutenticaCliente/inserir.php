<?php

	include_once("conexao.php");

	$id = $_POST['id'];
	$nome = $_POST['nome'];
	//$nome = "CURTIME()"; // Pega a hora do banco
	$inicio = $_POST['inicio'];
	$fim = $_POST['fim'];
	$ferias = $_POST['ferias'];
	$nivel = $_POST['nivel'];
	$uid = $_POST['uid'];

	$funcionarios = "insert into funcionarios values ('$id','$nome','$inicio','$fim', '$ferias', '$nivel', '$uid')";
	$resultado = mysqli_query($mysqli,$funcionarios);

	$redirect = "http://localhost:8080/AutenticaCliente/";
 	header("location:$redirect");

?>