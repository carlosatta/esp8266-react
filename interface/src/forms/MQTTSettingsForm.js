import React, { Fragment } from 'react';
import PropTypes from 'prop-types';

import { withStyles } from '@material-ui/core/styles';
import Button from '@material-ui/core/Button';
import LinearProgress from '@material-ui/core/LinearProgress';
import Checkbox from '@material-ui/core/Checkbox';
import { TextValidator, ValidatorForm } from 'react-material-ui-form-validator';
import Typography from '@material-ui/core/Typography';
import FormControlLabel from '@material-ui/core/FormControlLabel';
import Switch from '@material-ui/core/Switch';
import FormGroup from '@material-ui/core/FormGroup';

import isIP from '../validators/isIP';
import isHostname from '../validators/isHostname';
import or from '../validators/or';
import PasswordValidator from '../components/PasswordValidator';

const styles = theme => ({
  loadingSettings: {
    margin: theme.spacing(0.5),
  },
  loadingSettingsDetails: {
    margin: theme.spacing(4),
    textAlign: "center"
  },
  textField: {
    width: "100%"
  },
  checkboxControl: {
    width: "100%"
  },
  button: {
    marginRight: theme.spacing(2),
    marginTop: theme.spacing(2),
  }
});

class MQTTSettingsForm extends React.Component {

  componentWillMount() {
    ValidatorForm.addValidationRule('isIPOrHostname', or(isIP, isHostname));
  }

  render() {
    const { classes, mqttSettingsFetched, mqttSettings, errorMessage, handleValueChange, handleCheckboxChange, onSubmit, onReset } = this.props;

    return (
      <div>
        {
         !mqttSettingsFetched ?

         <div className={classes.loadingSettings}>
           <LinearProgress className={classes.loadingSettingsDetails}/>
           <Typography variant="h4" className={classes.loadingSettingsDetails}>
             Loading...
           </Typography>
         </div>

         : mqttSettings ?

      	 <ValidatorForm onSubmit={onSubmit}>

          <TextValidator
              validators={['required', 'isIPOrHostname']}
              errorMessages={['Hostname is required', "Not a valid IP address or hostname"]}
              name="hostname"
              label="Hostname"
              className={classes.textField}
              value={mqttSettings.hostname}
              onChange={handleValueChange('hostname')}
              margin="normal"
            />
          
          <TextValidator
              validators={['required','isNumber','minNumber:1','maxNumber:65535']}
              errorMessages={['Port is required','Port must be a number','Must be at least than 0',"Must not be more than 65535"]}
              name="port"
              label="Port"
              className={classes.textField}
              value={mqttSettings.port}
              type="number"
              onChange={handleValueChange('port')}
              margin="normal"
            />

            <TextValidator
              validators={['required']}
              errorMessages={['Base topic is required']}
              name="base_topic"
              label="Base topic"
              className={classes.textField}
              value={mqttSettings.base_topic}
              onChange={handleValueChange('base_topic')}
              margin="normal"
            />

          <TextValidator
              validators={['required','isNumber','minNumber:1']}
              errorMessages={['Keep Alive is required','Keep Alive must be a number','Must be at least 1 seconds']}
              name="keepAlive"
              label="Keep Alive (Seconds)"
              className={classes.textField}
              value={mqttSettings.keepAlive}
              type="number"
              onChange={handleValueChange('keepAlive')}
              margin="normal"
            />

          <FormGroup>
            <FormControlLabel
              control={<Switch checked={mqttSettings.cleanSession} onChange={handleCheckboxChange('cleanSession')} id="cleanSession" />}
              label="Clean Session?" 
            />
          </FormGroup>

          <TextValidator
            validators={['required','isNumber','minNumber:1']}
            errorMessages={['Timeout is required','Timeout must be a number','Must be at least 1 milliseconds']}
            name="timeout"
            label="Timeout (Seconds)"
            className={classes.textField}
            value={mqttSettings.timeout}
            type="number"
            onChange={handleValueChange('timeout')}
            margin="normal"
          />

          <FormControlLabel className={classes.checkboxControl}
              control={
                <Checkbox
                  value="haveCredentials"
                  checked={mqttSettings.haveCredentials}
                  onChange={handleCheckboxChange("haveCredentials")}
                />
              }
              label="Use credentials?"
            />

          {
            mqttSettings.haveCredentials &&
            <Fragment>
              <TextValidator
                validators={['matchRegexp:^[a-zA-Z0-9_\\.]{1,24}$']}
                errorMessages={["Must be 1-24 characters: alpha numeric, '_' or '.'"]}
                name="username"
                label="Username"
                className={classes.textField}
                value={mqttSettings.username}
                onChange={handleValueChange('username')}
                margin="normal"
              />
              <PasswordValidator
                validators={['matchRegexp:^.{1,64}$']}
                errorMessages={['Password must be 64 characters or less']}
                name="password"
                label="Password"
                className={classes.textField}
                value={mqttSettings.password}
                onChange={handleValueChange('password')}
                margin="normal"
              />
            </Fragment>
          }            

          <Button variant="contained" color="primary" className={classes.button} type="submit">
            Save
          </Button>
          <Button variant="contained" color="secondary" className={classes.button} onClick={onReset}>
      		  Reset
      		</Button>

         </ValidatorForm>

        :

        <div className={classes.loadingSettings}>
          <Typography variant="h4" className={classes.loadingSettingsDetails}>
            {errorMessage}
          </Typography>
          <Button variant="contained" color="secondary" className={classes.button} onClick={onReset}>
      		  Reset
      		</Button>
        </div>
      }
      </div>
    );
  }
}

MQTTSettingsForm.propTypes = {
  classes: PropTypes.object.isRequired,
  mqttSettingsFetched: PropTypes.bool.isRequired,
  mqttSettings: PropTypes.object,
  errorMessage: PropTypes.string,
  onSubmit: PropTypes.func.isRequired,
  onReset: PropTypes.func.isRequired,
  handleValueChange: PropTypes.func.isRequired,
};

export default withStyles(styles)(MQTTSettingsForm);
