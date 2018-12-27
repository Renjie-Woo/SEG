import os
from PIL import Image
import numpy as np
import matplotlib.pyplot as plt
import tensorflow as tf
from scipy.misc import imsave,imread
import nets

DATA_NAME = 'Data'
TRAIN_SOURCE = "Train"
TEST_SOURCE = 'Test'
RUN_NAME = "SELU_Run03"
OUTPUT_NAME = 'Output'
CHECKPOINT_FN = 'model.ckpt'

WORKING_DIR = os.getcwd()

TRAIN_DATA_DIR = os.path.join(WORKING_DIR, DATA_NAME, TRAIN_SOURCE)
TEST_DATA_DIR = os.path.join(WORKING_DIR, DATA_NAME, TEST_SOURCE)

ROOT_LOG_DIR = os.path.join(WORKING_DIR, OUTPUT_NAME)
LOG_DIR = os.path.join(ROOT_LOG_DIR, RUN_NAME)
CHECKPOINT_FL = os.path.join(LOG_DIR, CHECKPOINT_FN)

TRAIN_WRITER_DIR = os.path.join(LOG_DIR, TRAIN_SOURCE)
TEST_WRITER_DIR = os.path.join(LOG_DIR, TEST_SOURCE)

NUM_EPOCHS = 5
MAX_STEP = 1500
BATCH_SIZE = 1

LEARNING_RATE = 1e-04

SAVE_RESULTS_INTERVAL = 5
SAVE_CHECKPOINT_INTERVAL = 15

path = "Images_predict"
output_path = "Labels_predict"

def pic(input_image):
    image_get = imread(input_image)
    image_get = image_get[...,0][...,None]/255
    img = np.expand_dims(image_get,axis=0)
    return img

def main():
    train_data = nets.GetData(TRAIN_DATA_DIR)
    test_data = nets.GetData(TEST_DATA_DIR)

    g = tf.Graph()

    with g.as_default():

        images, labels = nets.placeholder_inputs(batch_size=BATCH_SIZE)

        logits, softmax_logits = nets.inference(images, class_inc_bg=2)

        nets.add_output_images(images=images, logits=logits, labels=labels)

        loss = nets.loss_calc(logits=logits, labels=labels)

        global_step = tf.Variable(0, name='global_step', trainable=False)

        train_op = nets.training(loss=loss, learning_rate=1e-04, global_step=global_step)

        pre_op = nets.output_labels(logits)

        accuracy = nets.evaluation(logits=logits, labels=labels)

        summary = tf.summary.merge_all()

        init = tf.global_variables_initializer()

        saver = tf.train.Saver(tf.global_variables())

    sm = tf.train.SessionManager(graph=g)

    with sm.prepare_session("", init_op=init, saver=saver, checkpoint_dir=LOG_DIR) as sess:

        sess.run(tf.local_variables_initializer())

        train_writer = tf.summary.FileWriter(TRAIN_WRITER_DIR, sess.graph)
        test_writer = tf.summary.FileWriter(TEST_WRITER_DIR)

        global_step_value, = sess.run([global_step])

        print("Last trained iteration was: ", global_step_value)

        try:

            while True:
                if global_step_value >= MAX_STEP:
                    print(f"Reached MAX_STEP: {MAX_STEP} at step: {global_step_value}")
                    break

                images_batch, labels_batch = test_data.next_batch(BATCH_SIZE)
                feed_dict = {images: images_batch, labels: labels_batch}

                if (global_step_value + 1) % SAVE_RESULTS_INTERVAL == 0:
                    _, loss_value, accuracy_value, global_step_value, summary_str = sess.run([train_op, loss, accuracy, global_step, summary], feed_dict=feed_dict)
                    train_writer.add_summary(summary_str, global_step=global_step_value)
                    print(f"TRAIN Step: {global_step_value}\tLoss: {loss_value}\tAccuracy: {accuracy_value}")


                    images_batch, labels_batch = train_data.next_batch(BATCH_SIZE)
                    feed_dict = {images: images_batch, labels: labels_batch}

                    loss_value, accuracy_value, global_step_value, summary_str = sess.run([loss, accuracy, global_step, summary], feed_dict=feed_dict)
                    test_writer.add_summary(summary_str, global_step=global_step_value)
                    print(f"TEST  Step: {global_step_value}\tLoss: {loss_value}\tAccuracy: {accuracy_value}")

                else:
                    _, loss_value, accuracy_value, global_step_value = sess.run([train_op, loss, accuracy, global_step], feed_dict=feed_dict)
                    print(f"TRAIN Step: {global_step_value}\tLoss: {loss_value}\tAccuracy: {accuracy_value}")

                if global_step_value % SAVE_CHECKPOINT_INTERVAL == 0:
                    print (global_step_value)
                    saver.save(sess, CHECKPOINT_FL, global_step=global_step_value)
                    print("Checkpoint Saved")

                if global_step_value == MAX_STEP:
                    print ("+++++++++++++++++++++++++++  predict  ++++++++++++++++++++++++++++++++")
                    for filename in os.listdir(path):
                        file = os.path.join(path,filename)
                        if not file.endswith((".png", ".jpg", ".gif")):
                            continue
                        images_batch = pic(file)
                        feed_dict = {images: images_batch}
                        op = sess.run([pre_op],feed_dict=feed_dict)
                        lab = np.squeeze(op,axis = None)
                        print(lab.shape)
                        opt_labels = os.path.join(output_path,filename)
                        imsave(opt_labels,lab)
                        print ("************************* ", filename,"Saved! **********************")

        except Exception as e:
            print('Exception')
            print(e)

        train_writer.flush()
        test_writer.flush()
        saver.save(sess, CHECKPOINT_FL, global_step=global_step_value)
        print("Checkpoint Saved")

        print("Stopping")


if __name__ == '__main__':
    main()

