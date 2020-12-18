<h2 class="maintitle"><?= $title ?></h2>
</div>
<div class="container">
	<div class="split left userpageleft">

	  </div>
	</div>

	<div class="split right">
		<?php if ($this->session->userID != 0) {
			echo '<p>You are logged in</p>
	  			<p>You can now acces your data</p>';

			echo form_open('Pages/logout_user');
			echo '<input type="submit" value="Logout">';
			echo '</form>';
		}
		else{
			echo "<p>You should login</p>
	  			<p>Then you can acces your data</p>";
	    echo form_open('Pages/login_user'); 
			echo '<input type="text" id="username" name="username" value="Username"><br>';
			echo '<input type="password" id="password" name="password" value="Password"><br><br>';
			echo '<input type="submit" value="Login">';
		echo '</form>';
		}?>
	  </div>
	</div>
</div>