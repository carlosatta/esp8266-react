import React, { Component } from 'react';

import { MQTT_SETTINGS_ENDPOINT }  from  '../constants/Endpoints';
import {restComponent} from '../components/RestComponent';
import SectionContent from '../components/SectionContent';
import MQTTSettingsForm from '../forms/MQTTSettingsForm';

class MQTTSettings extends Component {

  componentDidMount() {
      this.props.loadData();
  }

  render() {
    const { data, fetched, errorMessage } = this.props;
    return (
      <SectionContent title="MQTT Settings">
      	<MQTTSettingsForm
          mqttSettings={data}
          mqttSettingsFetched={fetched}
          errorMessage={errorMessage}
          onSubmit={this.props.saveData}
          onReset={this.props.loadData}
          handleValueChange={this.props.handleValueChange}
          handleCheckboxChange={this.props.handleCheckboxChange}
        />
      </SectionContent>
    )
  }

}

export default restComponent(MQTT_SETTINGS_ENDPOINT, MQTTSettings);
