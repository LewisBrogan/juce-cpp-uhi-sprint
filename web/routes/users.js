const express = require('express');
const router = express.Router();
const bcrypt = require('bcryptjs');


// user model
const User = require('../models/User');
// login page
router.get('/login', (req,res) => res.render('login'));
//register page
router.get('/register', (req,res) => res.render('register'));
//register handle
router.post('/register', (req, res) => {
    const { name, email, password, password2} = req.body;
    let errors = [];


// CHeck required field
if(!name || !email || !password || !password2){
    errors.push({mgs: 'Please, fill in all fields.'});
}
// Check passwords match
if(password !== password2) {
    errors.push({msg: 'Passwords do not match'});
}
// CHeck password length
if(password.length < 8){
    errors.push({msg: 'Password must be at least 8 characters'});
}
if(errors.length > 0){
    res.render('register',{
        errors,
        name, 
        email, 
        password, 
        password2
    });
}else{
    // form validation passed
    User.findOne({email: email})
    .then(user => {
        if(user) {
            errors.push({ msg: 'Email is already registered.'})
            res.render('register',{
                errors,
                name, 
                email, 
                password, 
                password2
            });
        } else {
            const newUser = new User({
                name,
                email,
                password
            });
        // Hash Password
        bcrypt.genSalt(10, (err, salt) => 
        bcrypt.hash(newUser.password, salt, (err, hash) =>{
            if(err) throw err;
            // hash password
            newUser.password = hash;
            // save user
            newUser.save()
                .then(user => {
                    req.flash('success_msg', 'You are now registered.')
                    res.redirect('/users/login');
            })
                .catch(err => console.log(err));
        }))

        

        }
    });
}


});


module.exports = router;