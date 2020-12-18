<h2 class="maintitle"><?= $title ?></h2>
<div class="container">
<div class="split left">
<?php
if ($this->session->userID != 0) {
	echo '<p>OPEN Door</p>';
	echo '<p style="font-size:0.8em;">Closes automatically</p>';
	echo form_open('Pages/open_door');
	echo '<input type="text" id="deviceid" name="deviceid" value="Device ID"><br>';
	echo '<input type="submit" value="Open">';
	echo '</form>';
	if ($this->session->flashdata('userdata')) {
		$input = $this->session->flashdata('userdata');
		echo $input;
	}
}?>
</div>
<div class="split right">
	<p>Check the Device ID</p>
	<?php
	if ($this->session->userID != 0) {
		$this-> db->select('idLaite, Sensori, Nimi');
		$this-> db->from('Laite');
		$this-> db->join('Firma', 'idFirma=Firma_idFirma');
		$query = $this-> db->get();

	echo "<table class='datatabletable'>
	    <tr class='datatable dataheader'>
	        <th class='datatable dataheader'>Device ID</th>
	        <th class='datatable dataheader'>Name</th>
	        <th class='datatable dataheader'>Company</th>
	    </tr>";

	foreach ($query->result() as $row)
	{
	    echo "<tr class='datatable'>";
	    echo "<td class='datatable'>". htmlspecialchars($row->idLaite) . "</td>";
	    echo "<td class='datatable'>" . htmlspecialchars($row->Sensori) . "</td>";
	    echo "<td class='datatable'>" . htmlspecialchars($row->Nimi) . "</td>";
	    
	    echo "</tr>";
	}
	echo "</table>";
	}?>
</div>
