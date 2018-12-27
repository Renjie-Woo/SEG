import tensorflow as tf

def output_labels(logits):
	labels = tf.argmax(logits, 3)
	return labels

