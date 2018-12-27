#__init__.py
This file is used for import;

#GetData.py
This file is used to patch '.png' pictures from folders 'Data' for feed;

#inputs.py
This file is used to define the placholder for input; 

#helpers.py
1. This file is used to make training visibly on TensorBoard;
2. >>> tf.summary.image('input', images, max_outputs=max_outputs) outputs the images input from '/Data/Images';
3. >>> tf.summary.image('input_labels_mixed', input_labels_image, max_outputs=3) outputs the labels input from 'Data/Labels';
4. >>> tf.summary.image('output_labels_mixed', output_labels_image, max_outputs=3) outputs the labels produced by parameter the SegNet learned;

#evaluation.py
This file is used to evaluate the accurracy of the similarity of the output labels with input labels;

#output.py
This file is used to produce the output_labels;

#training.py
This file is used for update the parameters and reload weights;

#inference.py
This file is used to define the net for training;

#layers.py
This file is used to unpooling layer after max_pool_with_argmax;