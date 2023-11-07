<?php
define('DB_HOST', 'fdb1033.awardspace.net');
define('DB_USERNAME','4374697_jakapat');
define('DB_PASSWORD','Jakapat12@');
define('DB_NAME','4374697_jakapat');

define('POST_DATA_URL','http://jakapatdb.atwebpages.com/sensordata.php');


define('PROJECT_API_KEY','jakapatmysqldht');

date_default_timezone_set('Asia/Bangkok');

$db = new mysqli(DB_HOST, DB_USERNAME , DB_PASSWORD , DB_NAME);


if ($db->connect_errno){
        echo "Connection to database is failed: ".$db->connect_error;
        exit();
// }else{
        //echo "Connected successfully";
}

?>
       