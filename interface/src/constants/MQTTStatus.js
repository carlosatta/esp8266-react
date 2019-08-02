import * as Highlight from '../constants/Highlight';

export const MQTT_TIME_NOT_SET = 0;
export const MQTT_TIME_NEEDS_SYNC = 1;
export const MQTT_TIME_SET = 2;

export const isSynchronized = mqttStatus => mqttStatus && (mqttStatus.status === MQTT_TIME_NEEDS_SYNC || mqttStatus.status === MQTT_TIME_SET);

export const mqttStatusHighlight = mqttStatus => {
  switch (mqttStatus.status){
    case MQTT_TIME_SET:
      return Highlight.SUCCESS;
    case MQTT_TIME_NEEDS_SYNC:
      return Highlight.WARN;
    case MQTT_TIME_NOT_SET:
    default:
      return Highlight.ERROR;
  }
}

export const mqttStatus = mqttStatus => {
  switch (mqttStatus.status){
    case MQTT_TIME_SET:
      return "Synchronized";
    case MQTT_TIME_NEEDS_SYNC:
      return "Synchronization required";
    case MQTT_TIME_NOT_SET:
      return "Time not set"
    default:
      return "Unknown";
  }
}
