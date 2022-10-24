const express = require("express")
const router = express.Router()
const fs = require("fs")
const { v4:uuidv4 } = require("uuid")

const rawData = fs.readFileSync("./api/data.json",{encoding:"utf-8"}).toString()
let data = JSON.parse(rawData)

console.log(data)

router.get("/pack/all",(rep,res) => {
  const show = []
  for (let i=0;i<data.length;i++)
  {
    show.push({"name":data[i]["name"],"description":data[i]["description"],"code":data[i]["code"]})
  }
  res.send(show)
})
router.post("/pack/post",(rep,res) => {
  const foundPackage = data.find((d) => d.name === rep.body.name)
  if (foundPackage)
  {
    res.send("database has package name like your package name.")
  }
  else {
    const keyUpdate = uuidv4()
    data.push({...rep.body,key:keyUpdate})
    fs.writeFileSync("./api/data.json",JSON.stringify(data),{encoding:"utf-8"})
    console.log(rep.body)
    res.send(`success! key update: ${keyUpdate}`)
  }
})
router.get("/pack/:name",(rep,res) => {
  const pack = data.find((d) => d.name == rep.params.name)
  //res.send({pack["name"],pack["code"]})
  res.send(`${pack["name"]},${pack["code"]}`)
})
router.delete("/pack/:name/:key",(rep,res) => {
  const k = data.find((d) => d.name == rep.params.name)
  if (k["key"] == rep.params.key)
  {

  data = data.filter((d) => d.name != rep.params.name )
  fs.writeFileSync("./api/data.json",JSON.stringify(data),{encoding:"utf-8"})
  res.send("success")
  } else {
    res.send("key error")
  }
})
//router.get("/pack/te123/:name/:key",(rep,res)=>{
router.patch("/pack/:name/:key",(rep,res)=>{
  const name = rep.params.name
  const key = rep.params.key
  const ud = data.find((d) => d.name === name)
  if (ud["key"] == key)
  {
    if (rep.body.code)
    {

      ud["code"] = rep.body.code
    }
    if (rep.body.description)
    {

      ud["description"] = rep.body.description
    }
    fs.writeFileSync("./api/data.json",JSON.stringify(data),{encoding:"utf-8"})
    res.send("success")
  }
  else 
  {
    res.send("key error")
  }
})
module.exports = router

