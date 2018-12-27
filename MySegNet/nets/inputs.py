import tensorflow as tf

def placeholder_inputs(batch_size):

    images = tf.placeholder(tf.float32, [batch_size, 768, 768, 1],name = 'images')
    labels = tf.placeholder(tf.int64, [batch_size, 768, 768, 1], name = 'labels')

    return images, labels
