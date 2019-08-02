import React, { Component } from 'react';
import { Redirect, Switch } from 'react-router-dom'

import Tabs from '@material-ui/core/Tabs';
import Tab from '@material-ui/core/Tab';

import AuthenticatedRoute from '../authentication/AuthenticatedRoute';
import MenuAppBar from '../components/MenuAppBar';
import MeasurementsStatus from '../containers/MeasurementsStatus';
import { withAuthenticationContext } from '../authentication/Context.js';

class Measurements extends Component {

  handleTabChange = (event, path) => {
    this.props.history.push(path);
  };

  render() {
    return (
      <MenuAppBar sectionTitle="Measurements">
        <Tabs value={this.props.match.url} onChange={this.handleTabChange} indicatorColor="primary" textColor="primary" variant="fullWidth">
          <Tab value="/measurements/status" label="Measurements" />
        </Tabs>
        <Switch>
          <AuthenticatedRoute exact={true} path="/measurements/status" component={MeasurementsStatus} />
          <Redirect to="/measurements/status" />
        </Switch>
      </MenuAppBar>
    )
  }
}

export default withAuthenticationContext(Measurements);
