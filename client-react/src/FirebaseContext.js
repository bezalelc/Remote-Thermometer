import React, { useContext, createContext, useState, useEffect } from "react";
import { initializeApp } from "firebase/app";
import { getDatabase, ref, onValue } from "firebase/database";
import { getAuth } from "firebase/auth";
import firebaseConfig from "./firebaseConfig";

const FirebaseContext = createContext()

const userTemplate = {
    userId: null,
    displayName: null,
    prob1: {
        temperature: 0,
        destTemperature: 0,
        startTime: 0,
        currentTime: 0
    },
    prob2: {
        temperature: 0,
        destTemperature: 0,
        startTime: 0,
        currentTime: 0
    },
    prob3: {
        temperature: 0,
        destTemperature: 0,
        startTime: 0,
        currentTime: 0
    },
    prob4: {
        temperature: 0,
        destTemperature: 0,
        startTime: 0,
        currentTime: 0
    },
    setting: {}
}

export function FirebaseProvider({ children }) {
    const [userId, setUserId] = useState(null)
    const firebaseApp = initializeApp(firebaseConfig);
    const firebaseDB = getDatabase(firebaseApp);
    const firebaseAuth = getAuth(firebaseApp);
    const [data, setData] = useState(userTemplate)
    const dbRef = ref(firebaseDB, '/UsersData/' + userId)

    useEffect(() => {
        firebaseAuth.onAuthStateChanged((user) => {
            if (user) {
                setUserId(user.uid)
                // setCurrentUser({
                //     ...data,
                //     displayName: user.displayName
                // })
            }
        });
    }, [firebaseAuth]);


    useEffect(() => {
        onValue(dbRef, (snapshot) => {
            setData(data => ({
                ...data,
                ...snapshot.val()
            }))
        })
    }, [userId])

    return (
        <FirebaseContext.Provider value={{
            data,
            userId,
            setUserId,
            firebaseDB,
            firebaseAuth
        }}>
            {children}
        </FirebaseContext.Provider>
    );
}

export function useFirebase() {
    return useContext(FirebaseContext)
};