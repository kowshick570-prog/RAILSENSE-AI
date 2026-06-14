#include "inference.h"
#include "anomaly_model.h"   // Generated from train_model.py output
#include <TensorFlowLite_ESP32.h>
#include "tensorflow/lite/micro/all_ops_resolver.h"
#include "tensorflow/lite/micro/micro_interpreter.h"
#include "tensorflow/lite/micro/micro_error_reporter.h"
#include "tensorflow/lite/schema/schema_generated.h"

namespace {
  const tflite::Model* model = nullptr;
  tflite::MicroInterpreter* interpreter = nullptr;
  TfLiteTensor* input = nullptr;
  TfLiteTensor* output = nullptr;

  constexpr int kTensorArenaSize = 8 * 1024;
  uint8_t tensorArena[kTensorArenaSize];
}

void initModel() {
  model = tflite::GetModel(railsense_anomaly_model_tflite);

  static tflite::AllOpsResolver resolver;
  static tflite::MicroInterpreter static_interpreter(
      model, resolver, tensorArena, kTensorArenaSize);
  interpreter = &static_interpreter;

  interpreter->AllocateTensors();
  input  = interpreter->input(0);
  output = interpreter->output(0);

  Serial.println("TFLite anomaly detection model loaded.");
}

float runInference(float* features) {
  for (int i = 0; i < input->dims->data[1]; i++) {
    input->data.f[i] = features[i];
  }

  if (interpreter->Invoke() != kTfLiteOk) {
    Serial.println("ERROR: Inference failed.");
    return -1.0;
  }

  // Output: single anomaly score normalized between 0 and 1
  return output->data.f[0];
}
