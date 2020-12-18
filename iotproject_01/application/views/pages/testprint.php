<h2 class="maintitle"><?= $title ?></h2>

<?php
$query = $this->db->query('SELECT * FROM users');

echo "<table class='usertable usertabletable'>
    <tr class='usertable'>
        <th class='usertable'>ID</th>
        <th class='usertable'>Username</th>
        <th class='usertable'>Password</th>
    </tr>";

foreach ($query->result() as $row)
{
    echo "<tr class='usertable'>";
    echo "<td class='usertable'>". htmlspecialchars($row->id) . "</td>";
    echo "<td class='usertable'>" . htmlspecialchars($row->username) . "</td>";
    echo "<td class='usertable'>" . htmlspecialchars($row->password) . "</td>";
    echo "</tr>";
}
echo "</table>";

?>