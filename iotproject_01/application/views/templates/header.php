<html>
	<meta name="viewport" content="width=device-width, initial-scale=1.0">
		<head>
			<title>Ryhmä1</title>
			<link rel="stylesheet" href="assets/css/oma_dark.css">
		</head>
		<body>
		<nav>
	      <div class="containernav">
	      	<?php if ($this->session->userID != 0) {?>
		      	<div>
		          <ul style="list-style-type: none;">
		          	<li><a href="<?php echo base_url(); ?>">Home</a></li>
		          	<li><a href="<?php echo base_url(); ?>contacts">Contacts</a></li>
		          	<li style="float:right; border-left:1px solid #616161; border-right:0px;"><a href="<?php echo base_url(); ?>user">
		          	User</a></li>
		          	<li style="float:right; border-left:1px solid #616161; border-right:0px;"><a href="<?php echo base_url(); ?>devices">
		          	Devices</a></li>
		          	<li style="float:right; border-left:1px solid #616161; border-right:0px;"><a href="<?php echo base_url(); ?>data">
		          	Data</a></li>
		          </ul>
		        </div>
	      	<?php } 
	      	else{?>
		        <div>
		          <ul style="list-style-type: none; ">
		          	<li><a href="<?php echo base_url(); ?>">Home</a></li>
		          	<li><a href="<?php echo base_url(); ?>contacts">Contacts</a></li>
		          	<li style="float:right; border-left:1px solid #616161; border-right:0px;"><a href="<?php echo base_url(); ?>user">User</a></li>
		          </ul>
		        </div>
	    	<?php } ?>
	      </div>
	    </nav>

	    <div class="container">