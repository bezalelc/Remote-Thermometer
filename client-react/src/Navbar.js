import { useFirebase } from './FirebaseContext'
import { Link, useLocation } from 'react-router-dom'
import './style/Navbar.css'

const Navbar = () => {
    const { firebaseAuth, userId, setUserId } = useFirebase()
    const location = useLocation();

    const logoutHandler = () => {
        firebaseAuth.signOut()
            .then(() => {
                setUserId(null)
            })
            .catch((error) => {
                console.error('Error logging out:', error);
            });
    }


    return (
        <nav className="navbar-container">
            <div className='navbar-buttons'>
                {location.pathname === '/home' && <Link to="/config"><button>Setting</button></Link>}
                {location.pathname === '/config' && <Link to="/home"><button >Home</button></Link>}
                {userId && <button className='navbar-logout-button' onClick={logoutHandler}>Logout</button>}
            </div>
            <div className='navbar-title'>Remote Thermometer</div>
        </nav >
    );
}

export default Navbar;