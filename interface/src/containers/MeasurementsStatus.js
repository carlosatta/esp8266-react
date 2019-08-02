import React, { Component } from 'react';

import { withStyles } from '@material-ui/core/styles';

// import { SYSTEM_STATUS_ENDPOINT } from '../constants/Endpoints';
// import { restComponent } from '../components/RestComponent';
import SectionContent from '../components/SectionContent';

const styles = theme => ({
  fetching: {
    margin: theme.spacing(4),
    textAlign: "center"
  },
  button: {
    marginRight: theme.spacing(2),
    marginTop: theme.spacing(2),
  }
});

class MeasurementsStatus extends Component {

  componentDidMount() {
    // this.props.loadData();
  }

  render() {
    return (
      <SectionContent title="Measurements">
        <div>
          { JSON.stringify(this.props) }
        </div>
      </SectionContent>
    )
  }
}

// export default restComponent(SYSTEM_STATUS_ENDPOINT, withStyles(styles)(MeasurementsStatus));
export default  withStyles(styles)(MeasurementsStatus);
