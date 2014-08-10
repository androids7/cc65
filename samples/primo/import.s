
	.export _driver
	.import _digitalWrite
	.segment "DRVCODE"
_driver:
	.word _digitalWrite
