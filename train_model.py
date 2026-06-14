"""
RAILSENSE AI - Anomaly Detection Model Training Script
--------------------------------------------------------
Trains a lightweight autoencoder-based anomaly detection model on
track sensor data (vibration, temperature, current) and converts it
to TensorFlow Lite format for deployment on the ESP32 node.
"""

import numpy as np
import pandas as pd
import tensorflow as tf
from tensorflow import keras
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler

# ---------- 1. Load Dataset ----------
DATA_PATH = "dataset_sample.csv"
df = pd.read_csv(DATA_PATH)

FEATURE_COLUMNS = [
    "accel_x", "accel_y", "accel_z",
    "gyro_x", "gyro_y", "gyro_z",
    "temperature", "current"
]

X = df[FEATURE_COLUMNS].values

# ---------- 2. Normalize ----------
scaler = StandardScaler()
X_scaled = scaler.fit_transform(X)

X_train, X_val = train_test_split(X_scaled, test_size=0.2, random_state=42)

# ---------- 3. Build Autoencoder ----------
input_dim = X_train.shape[1]

model = keras.Sequential([
    keras.layers.Input(shape=(input_dim,)),
    keras.layers.Dense(6, activation="relu"),
    keras.layers.Dense(3, activation="relu"),
    keras.layers.Dense(6, activation="relu"),
    keras.layers.Dense(input_dim, activation="linear")
])

model.compile(optimizer="adam", loss="mse")
model.summary()

# ---------- 4. Train ----------
history = model.fit(
    X_train, X_train,
    epochs=50,
    batch_size=16,
    validation_data=(X_val, X_val)
)

# ---------- 5. Wrap as anomaly score model ----------
class AnomalyScoreModel(keras.Model):
    def __init__(self, autoencoder, threshold):
        super().__init__()
        self.autoencoder = autoencoder
        self.threshold = threshold

    def call(self, x):
        reconstructed = self.autoencoder(x)
        error = tf.reduce_mean(tf.square(x - reconstructed), axis=1)
        score = tf.clip_by_value(error / self.threshold, 0.0, 1.0)
        return tf.expand_dims(score, axis=-1)

# Estimate threshold as 95th percentile of training reconstruction error
reconstructions = model.predict(X_train)
mse = np.mean(np.square(X_train - reconstructions), axis=1)
threshold = np.percentile(mse, 95)
print(f"Anomaly threshold (95th percentile MSE): {threshold:.5f}")

wrapped_model = AnomalyScoreModel(model, threshold)
wrapped_model.build(input_shape=(None, input_dim))

# ---------- 6. Convert to TFLite ----------
converter = tf.lite.TFLiteConverter.from_keras_model(wrapped_model)
converter.optimizations = [tf.lite.Optimize.DEFAULT]
tflite_model = converter.convert()

with open("railsense_anomaly_model.tflite", "wb") as f:
    f.write(tflite_model)

print("Saved railsense_anomaly_model.tflite")
print("\nNext step - convert to a C header for ESP32 deployment:")
print("  xxd -i railsense_anomaly_model.tflite > anomaly_model.h")
print("  (then rename the array/length vars to 'railsense_anomaly_model_tflite')")
