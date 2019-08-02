import React, { Component, Fragment } from 'react';

import { withStyles } from '@material-ui/core/styles';
import Button from '@material-ui/core/Button';
import LinearProgress from '@material-ui/core/LinearProgress';
import Typography from '@material-ui/core/Typography';
import List from '@material-ui/core/List';
import ListItem from '@material-ui/core/ListItem';
import ListItemAvatar from '@material-ui/core/ListItemAvatar';
import ListItemText from '@material-ui/core/ListItemText';
import Avatar from '@material-ui/core/Avatar';
import Divider from '@material-ui/core/Divider';
import UpdateIcon from '@material-ui/icons/Update';

import { mqttStatusHighlight, mqttStatus } from '../constants/MQTTStatus';
import * as Highlight from '../constants/Highlight';
import { MQTT_STATUS_ENDPOINT } from '../constants/Endpoints';
import { restComponent } from '../components/RestComponent';
import SectionContent from '../components/SectionContent';

// import moment from 'moment';

const styles = theme => ({
  ["mqttStatus_" + Highlight.SUCCESS]: {
    backgroundColor: theme.palette.highlight_success
  },
  ["mqttStatus_" + Highlight.ERROR]: {
    backgroundColor: theme.palette.highlight_error
  },
  ["mqttStatus_" + Highlight.WARN]: {
    backgroundColor: theme.palette.highlight_warn
  },
  fetching: {
    margin: theme.spacing(4),
    textAlign: "center"
  },
  button: {
    marginRight: theme.spacing(2),
    marginTop: theme.spacing(2),
  }
});

class MQTTStatus extends Component {

  componentDidMount() {
    this.props.loadData();
  }

  createListItems(data, classes) {
    return (
      <Fragment>
        <ListItem >
          <ListItemAvatar>
            <Avatar className={classes["mqttStatus_" + mqttStatusHighlight(data)]}>
              <UpdateIcon />
            </Avatar>
          </ListItemAvatar>
          <ListItemText primary="Status" secondary={mqttStatus(data)} />
        </ListItem>
        <Divider variant="inset" component="li" />
      </Fragment>
    );
  }

  renderMQTTStatus(data, classes) {
    return (
      <div>
        <List>
          {this.createListItems(data, classes)}
        </List>
        <Button variant="contained" color="secondary" className={classes.button} onClick={this.props.loadData}>
          Refresh
        </Button>
      </div>
    );
  }

  render() {
    const { data, fetched, errorMessage, classes } = this.props;

    return (
      <SectionContent title="MQTT Status">
        {
          !fetched ?
            <div>
              <LinearProgress className={classes.fetching} />
              <Typography variant="h4" className={classes.fetching}>
                Loading...
              </Typography>
            </div>
            :
            data ? this.renderMQTTStatus(data, classes)
              :
              <div>
                <Typography variant="h4" className={classes.fetching}>
                  {errorMessage}
                </Typography>
                <Button variant="contained" color="secondary" className={classes.button} onClick={this.props.loadData}>
                  Refresh
                </Button>
              </div>
        }
      </SectionContent>
    )
  }
}

export default restComponent(MQTT_STATUS_ENDPOINT, withStyles(styles)(MQTTStatus));
