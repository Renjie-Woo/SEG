## Aims
1. Used for extractment of teeth from a CT scan, for later reconstruction of 3D teeth models

## Requirements
You must have a GPU and install the tensorflow-gpu version as the cpu version does not have tf.nn.max_pool_with_argmax()
1. Python >=3.6: Best to use the [Conda](https://www.continuum.io/downloads) distribution
2. tensorflow-gpu >=0.11

## Usage
Make sure you have conda and tensorflow installed
File train.py is used only for train and train&predict.py is used for both train and predict
File Images_predict and Labels_predict is used for images to predict and to hold the predicted images

```commandline
python train.py
or
python train&predict.py

And in another terminal window start tensorboard
```commandline
tensorboard --logdir ./Output
```
Then in your webbrowser go to [http://localhost:6006](http://localhost:6006)

## Training and test data
The data is annotated by ourselves ,using Photoshop and js-segment-annotator.

## With thanks to
[andreaazzini/segnet](https://github.com/andreaazzini/segnet): A Tensorflow SegNet translation

[StackOverflow Tensorflow batch_norm thread](http://stackoverflow.com/questions/40081697/getting-low-test-accuracy-using-tensorflow-batch-norm-function)

[GitHub Tensorflow unpool thread](https://github.com/tensorflow/tensorflow/issues/2169)

[Github SegNetCMR](https://github.com/mshunshin/SegNetCMR)
