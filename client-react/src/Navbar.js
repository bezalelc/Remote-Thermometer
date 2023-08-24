import { useFirebase } from './FirebaseContext'
import './style/Navbar.css'

const Navbar = () => {
    const { firebaseAuth, userId, setUserId } = useFirebase()

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
            {userId && <button className='navbar-logout-button' onClick={logoutHandler}>Logout</button>}
            <div className='navbar-title'>Remote Thermometer</div>
        </nav>
    );
}

export default Navbar;