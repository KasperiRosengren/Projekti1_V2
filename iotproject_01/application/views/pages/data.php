<h2 class="maintitle"><?= $title ?></h2>
</div>
<div class="container">
<div class="split left">

	<p>Search who the tag belongs to or what tag someone owns</p>
	<p>If you are looking with name, the format is:</p>
	<p>Firstname,Lastname</p>
	<?php echo form_open('Pages/testform'); ?>
	<input type="text" id="input" name="input" value="Input"><br>

	<input class="radiobutton" type="radio" id="UID" name="type" value="UID">
	<label class="radiolabel" for="UID">UID</label><br>

	<input class="radiobutton" type="radio" id="user" name="type" value="user">
	<label class="radiolabel" for="user">User</label><br>

	<input type="submit" value="Search">
</form>
<div class="container">

<?php
	if ($this->session->flashdata('userdata')) {
		$input = $this->session->flashdata('userdata');

	 	if ($input['datatype'] == 'UID') {
	 		$this-> db->select('UID, Etunimi, Sukunimi');
			$this-> db->from('RFIDtag');
			$this-> db->join('Kayttajat', 'Kayttajat_idKayttajat=idKayttajat');
			$this-> db->where('UID', $input['value1']);
			$query = $this-> db->get();

			echo"
			<table class='datatabletable'>
		    	<tr class='datatable'>
		        <th class='datatable'>UID</th>
		        <th class='datatable'>Firstname</th>
		        <th class='datatable'>Lastname</th>
	    	</tr>";

	    	foreach ($query->result() as $row)
			{
			    echo "<tr class='datatable'>";
			    echo "<td class='datatable'>". htmlspecialchars($row->UID) . "</td>";
			    echo "<td class='datatable'>" . htmlspecialchars($row->Etunimi) . "</td>";
			    echo "<td class='datatable'>" . htmlspecialchars($row->Sukunimi) . "</td>";
			    echo "</tr>";
			}
			echo "</table>";
	 	}
	 	else{
	 		$this-> db->select('UID, Etunimi, Sukunimi, Nimi');
			$this-> db->from('RFIDtag');
			$this-> db->join('Kayttajat', 'Kayttajat_idKayttajat=idKayttajat');
			$this-> db->join('Firma', 'idFirma=Firma_idFirma');
			$this-> db->where('Etunimi', $input['value1']);
			$this-> db->where('Sukunimi', $input['value2']);
			$query = $this-> db->get();

			echo"
			<table class='datatabletable'>
		    	<tr class='datatable'>
		        <th class='datatable'>UID</th>
		        <th class='datatable'>Firstname</th>
		        <th class='datatable'>Lastname</th>
		        <th class='datatable'>Company</th>
	    	</tr>";

	    	foreach ($query->result() as $row)
			{
			    echo "<tr class='datatable'>";
			    echo "<td class='datatable'>". htmlspecialchars($row->UID) . "</td>";
			    echo "<td class='datatable'>" . htmlspecialchars($row->Etunimi) . "</td>";
			    echo "<td class='datatable'>" . htmlspecialchars($row->Sukunimi) . "</td>";
			    echo "<td class='datatable'>" . htmlspecialchars($row->Nimi) . "</td>";
			    echo "</tr>";
			}
			echo "</table>";
	 	}
	}

?>
</div>
</div>

<div class="split right">
	<p>Get every action on the devices your useraccount has acces to.</p>
	<div class="datapagetable">
	<?php
	if ($this->session->userID != 0) {
		$this-> db->select('Data, Sensori, Date');
		$this-> db->from('Data');
		$this-> db->join('Laite', 'Data.Laite_idLaite = idLaite');
		$this-> db->join('Firma', 'idFirma = Laite.Firma_idFirma');
		$this-> db->join('Kayttajat', 'Kayttajat.Firma_idFirma = idFirma');
		$this-> db->join('LoginUsers', 'idKayttajat = Kayttajat_idKayttajat');
		$this-> db->where('idLoginUsers', $this->session->userID);
		$this-> db->where('(idData % 2) = 1');
		$this-> db->ORDER_BY('Date', 'desc');
		$query = $this-> db->get();

	echo "<table class='datatabletable'>
	    <tr class='datatable dataheader'>
	        <th class='datatable dataheader'>UID</th>
	        <th class='datatable dataheader'>Device</th>
	        <th class='datatable dataheader'>Time</th>
	    </tr>";

	foreach ($query->result() as $row)
	{
	    echo "<tr class='datatable'>";
	    echo "<td class='datatable'>". htmlspecialchars($row->Data) . "</td>";
	    echo "<td class='datatable'>" . htmlspecialchars($row->Sensori) . "</td>";
	    echo "<td class='datatable'>" . htmlspecialchars($row->Date) . "</td>";
	    
	    echo "</tr>";
	}
	echo "</table>";
	}?>
</div>
</div>
</div>