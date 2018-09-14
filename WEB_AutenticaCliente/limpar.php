<?php

	include_once("conexao.php");

	$funcionarios = "truncate funcionarios";
	$resultado = mysqli_query($mysqli,$funcionarios);

	$redirect = "http://localhost:8080/AutenticaCliente/";
 	header("location:$redirect");