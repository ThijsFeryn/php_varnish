--TEST--
Check for varnish set/get params
--SKIPIF--
<?php if (!extension_loaded("varnish") || !file_exists('tests/config.php')) print "skip"; ?>
--FILE--
<?php 

include 'tests/config.php';

/* XXX test exceptions */

foreach ($args_all as $args) {
	$args['timeout'] = 1500;

	$va = new VarnishAdmin($args);
	$va->connect();
	$va->auth();

 	$va->setParam("thread_pools", 20);
 	$vparams = $va->getParams();
	echo (int)$vparams['thread_pools'] . "\n";

 	$va->setParam("thread_pools", 30);
 	$vparams = $va->getParams();
	echo (int)$vparams['thread_pools'] . "\n";

 	$va->setParam("thread_pools", 40);
 	$vparams = $va->getParams();
	echo (int)$vparams['thread_pools'] . "\n";
}

?>
--EXPECT--
20
30
40
20
30
40
20
30
40
20
30
40
