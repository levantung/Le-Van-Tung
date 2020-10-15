$result=mysql_query("select*from testwebsite");
while($row=mysql_fetch_array($result))
{
	echo "<tr>";
	echo "<form><input type='hidden' name ='MODE' value='UPDATE'>";
	for($i=0;$i<mysql_num_fields($result);$i++)
	if($i==0)
		echo "<td><input type=hidden name="
			mysql_field_name($result,$i)."value=".
$row[mysql_field_name($result,$i)].
		">".
		$row[mysql_field_name($result,$i)].
		"<td>";
			else
				echo "<td><input type=text name=".
						mysql_field_name($result,$i).
						"value=".
						$row[mysql_field_name($result,$i)].
						"></td>";
				echo"<td><input type='submit'value='edit'></form>";
				echo"<a href='?ID=".
				$row[mysql_field_name($result,0)].
				"&MODE='DELETE'>delete</a>";
			echo"</td></tr>;
}
mysql_free_result($result);
mysql_close($con);