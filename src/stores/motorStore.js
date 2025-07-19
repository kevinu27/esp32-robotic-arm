import { defineStore } from 'pinia'

export const useMotorStore = defineStore('motor', {
  state: () => ({
    motorBaseString: '',
    motorHombroString:'',
    motorCodoString:'',
    
  }),
 

  actions: {
    setMotorBaseString(str) {
      this.motorBaseString = str
      console.log('this.motorBaseString', this.motorBaseString)
    },
        setMotorHombroString(str) {
      this.motorHombroString = str
      console.log('this.motorHombroString', this.motorHombroString)
    },
        setMotorCodoString(str) {
      this.motorCodoString = str
      console.log('this.motorCodoString', this.motorCodoString)
    }
  }
})