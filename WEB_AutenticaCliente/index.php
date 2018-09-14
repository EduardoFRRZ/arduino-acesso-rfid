<?php
	include("consulta.php");
?>

<!DOCTYPE html>
<html>
	<head>
		<meta charset="utf-8">
		<title>Conexão com Banco</title>
		<link rel="stylesheet" type="text/css" href="style.css">
		<link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/bootstrap/4.1.3/css/bootstrap.min.css" integrity="sha384-MCw98/SFnGE8fJT3GXwEOngsV7Zt27NXFoaoApmYm81iuXoPkFOJwJ8ERdknLPMO" crossorigin="anonymous">
	</head>
	<body background="img/fundo.jpg">

		<h1 align="center">CONEXÃO COM O MYSQL</h1>

		<div class="container">	

			<div class="row">
				<div class="col">

					<div class="form">
						<h4 align="center">Cadastro Funcionario</h4>
						<form method="POST" action="inserir.php">
								
							</br>

							<label>ID</label>
							
							<input class="form-control" type="text" name="id">

							

							<label>Nome</label>
							</br>
							<input class="form-control" type="text" name="nome">

							

							<label>Inicio</label>
							
							<input class="form-control" type="text" name="inicio">

							

							<label>Fim</label>
							</br>
							<input class="form-control" type="text" name="fim">

							

							<label>Ferias</label>
							</br>
							<input class="form-control" type="text" name="ferias">

							

							<label>Nivel</label>
							
							<input class="form-control" type="text" name="nivel">

							</br>

							<label>UID</label>
							
							<input class="form-control" type="text" name="uid">

							</br>

							<input class="btn btn-primary btn-lg" type="submit" value="Enviar">
						</form>

					</div>
				</div>

				<div class="col">

					<table class="table table-striped table-dark">
					
						<tr>
							<td scope="col"><form action="limpar.php"><input class="btn btn-danger btn-sm" type="submit" value="Limpar"></form></td>
							<td scope="col">ID</td>
							<td scope="col">Nome</td>
							<td scope="col">Inicio</td>
							<td scope="col">Fim</td>
							<td scope="col">Ferias</td>
							<td scope="col">Nivel</td>
							<td scope="col">UID</td>
						</tr>
						
						<?php while($dado = $con->fetch_array()){ ?>
						<tr>
							<td>#</td>
							<td><?php echo $dado["Id"]; ?></td>
							<td><?php echo $dado["Nome"]; ?></td>
							<td><?php echo $dado["Inicio"]; ?></td>
							<td><?php echo $dado["Fim"]; ?></td>
							<td><?php echo $dado["Ferias"]; ?></td>
							<td><?php echo $dado["Nivel"]; ?></td>
							<td><?php echo $dado["uid"]; ?></td>
						</tr>
						<?php } ?>
					</table>
				</div>
			</div>	
		</div>

		<script src="https://code.jquery.com/jquery-3.3.1.slim.min.js" integrity="sha384-q8i/X+965DzO0rT7abK41JStQIAqVgRVzpbzo5smXKp4YfRvH+8abtTE1Pi6jizo" crossorigin="anonymous"></script>
		<script src="https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.14.3/umd/popper.min.js" integrity="sha384-ZMP7rVo3mIykV+2+9J3UJ46jBk0WLaUAdn689aCwoqbBJiSnjAK/l8WvCWPIPm49" crossorigin="anonymous"></script>
		<script src="https://stackpath.bootstrapcdn.com/bootstrap/4.1.3/js/bootstrap.min.js" integrity="sha384-ChfqqxuZUCnJSK3+MXmPNIyE6ZbWh2IMqE241rYiqJxyMiZ6OW/JmZQ5stwEULTy" crossorigin="anonymous"></script>
	</body>
</html>