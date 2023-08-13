import React from 'react';
import { Route, Redirect } from 'react-router-dom';
import { useFirebase } from './FirebaseContext';


function PrivateRoute({ component: Component, ...rest }) {
  const { userId } = useFirebase();


  return (
    <Route
      {...rest}
      render={(props) =>
        userId ? <Component {...props} /> : <Redirect to="/" />
      }
    />
  );
}

export default PrivateRoute;
