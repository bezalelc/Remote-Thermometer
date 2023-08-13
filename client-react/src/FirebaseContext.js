import React, { useContext, createContext, useState, useEffect } from "react";
import { initializeApp } from "firebase/app";
import { getDatabase } from "firebase/database";
import { getAuth } from "firebase/auth";
import firebaseConfig from "./firebaseConfig";

const FirebaseContext = createContext()

const currentUderTemplate = {
    displayName: null
}

export function FirebaseProvider({ children }) {
    const [userId, setUserId] = useState(null)
    const [currentUser, setCurrentUser] = useState(null)
    const firebaseApp = initializeApp(firebaseConfig);
    const firebaseDB = getDatabase(firebaseApp);
    const firebaseAuth = getAuth(firebaseApp);

    useEffect(() => {
        firebaseAuth.onAuthStateChanged((user) => {
            if (user) {
                setUserId(user.uid)
                setCurrentUser({
                    ...currentUderTemplate,
                    displayName: user.displayName
                })
            }
        });
    }, [firebaseAuth]);

    return (
        <FirebaseContext.Provider value={{ userId, setUserId, currentUser, setCurrentUser, firebaseDB, firebaseAuth }}>
            {children}
        </FirebaseContext.Provider>
    );
}

export function useFirebase() {
    return useContext(FirebaseContext)
};