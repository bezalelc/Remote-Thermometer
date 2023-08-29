import { BrowserRouter as Router, Route, Switch } from 'react-router-dom';
import { FirebaseProvider } from './FirebaseContext';
import Login from './Login';
import Home from './Home';
import PrivateRoute from './PrivateRoute';
import Navbar from './Navbar';
import ConfigPage from './ConfigPage'
import './style/App.css';

function App() {

  return (
    <FirebaseProvider>
      <Router>
        <div className="App">
          <video autoPlay loop muted playsInline className="app-background-video">
            <source src="/resources/video/background22.mp4" type="video/mp4" />
          </video>
          <Navbar />
          <Switch>
            <Route exact path='/' component={Login} />
            <PrivateRoute path='/home' component={Home} />
            <Route exact path='/config' component={ConfigPage} />
          </Switch>
        </div>
      </Router>
    </FirebaseProvider>
  );
}

export default App;
