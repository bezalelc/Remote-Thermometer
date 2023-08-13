import { useState, useEffect } from "react"
import { useHistory } from 'react-router-dom'
import { useFirebase } from './FirebaseContext';
import { signInWithEmailAndPassword, GoogleAuthProvider, signInWithPopup } from "firebase/auth";
import { FontAwesomeIcon } from '@fortawesome/react-fontawesome';
import { faGoogle, faFacebook } from '@fortawesome/free-brands-svg-icons';
import './style/Login.css';



const Login = () => {
    const [email, setEmail] = useState('')
    const [password, setPassword] = useState('')
    const { userId, firebaseAuth } = useFirebase()
    const history = useHistory()

    useEffect(() => {
        if (userId) {
            history.push('/home')
        }
    }, [userId, history]);


    const loginWithEmailPasswordHandler = (event) => {
        signInWithEmailAndPassword(firebaseAuth, email, password)
            .then(() => {
            })
            .catch((error) => {
                console.log(error.code)
                console.log(error.message)
                console.log(error)
            });
    }

    const loginWithGoogleHandler = async () => {
        const googleAuthProvider = new GoogleAuthProvider();

        signInWithPopup(firebaseAuth, googleAuthProvider)
            .then(() => {
                // This gives you a Google Access Token. You can use it to access the Google API.
                // const credential = GoogleAuthProvider.credentialFromResult(result);
                // const token = credential.accessToken;
                // // The signed-in user info.
                // const user = result.user;
                // IdP data available using getAdditionalUserInfo(result)
                // ...
            }).catch((error) => {
                const errorCode = error.code;
                const errorMessage = error.message;
                console.log(errorCode)
                console.log(errorMessage)
            });
    }


    return (
        <div className="login-container" >
            <form className="login-form" onSubmit={(e) => e.preventDefault()}>
                <h1>Login</h1>
                <label htmlFor="email" className="login-label">Email</label>
                <input type="email" className="login-input" placeholder="youremail@mail.com" value={email} onChange={(event) => setEmail(event.target.value)} required />
                <label htmlFor="password" className="login-label">Password</label>
                <input type="password" className="login-input" placeholder="********" value={password} onChange={(event) => setPassword(event.target.value)} required />
                <button type="submit" className="login-button" onClick={loginWithEmailPasswordHandler}>Log In</button>
                <div className="login-social">
                    <button className="login-social-google" onClick={loginWithGoogleHandler}><FontAwesomeIcon icon={faGoogle} />  Google</button>
                    <button className="login-social-facebook"><FontAwesomeIcon icon={faFacebook} className="login-social-facebook-icon" />  Facebook</button>
                </div>
            </form>
        </div>
    );
}

export default Login