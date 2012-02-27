--TEST--
Check for the basic VarnishLog::getLine() functionality
--SKIPIF--
<?php if (!extension_loaded("varnish") || !file_exists('tests/config.php')) print "skip"; ?>
--FILE--
<?php 

include 'tests/config.php';

foreach (array_slice($args_all, 0, 2) as $args) {
	$i = 3;
	$vs = new VarnishLog($args);
	while($i-- > 0) {
			$line = $vs->getLine();
			echo (int)is_array($line), "\n";
			echo (int)!empty($line), "\n";
	}
}

?>
--EXPECT--
1
1
1
1
1
1
1
1
1
1
1
1
