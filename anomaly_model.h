#ifndef ANOMALY_MODEL_H
#define ANOMALY_MODEL_H

// Placeholder for the converted TFLite model byte array.
//
// Steps to generate this file:
//   1. Run ml/train_model.py to produce railsense_anomaly_model.tflite
//   2. Convert to a C array:
//        xxd -i railsense_anomaly_model.tflite > anomaly_model.h
//   3. Rename the generated array + length variables to match below.

extern const unsigned char railsense_anomaly_model_tflite[];
extern const unsigned int railsense_anomaly_model_tflite_len;

#endif
