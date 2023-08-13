import './style/App.css';
import { BrowserRouter as Router, Route, Switch } from 'react-router-dom';
import { FirebaseProvider } from './FirebaseContext';
import Login from './Login';
import Home from './Home';
import PrivateRoute from './PrivateRoute';
import Navbar from './Navbar';

function App() {
  return (
    <FirebaseProvider>
      <Router>
        <div className="App">
        <Navbar />
          <Switch>
            <Route exact path='/' component={Login} />
            <PrivateRoute path='/home' component={Home} />
          </Switch>
        </div>
      </Router>
    </FirebaseProvider>
  );
}

export default App;
