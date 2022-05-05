//index.js
//获取应用实例
var app = getApp()
Page({
  data: {
    imgUrls: [
      'https://timgsa.baidu.com/timg?image&quality=80&size=b9999_10000&sec=1582798380580&di=340989da2df613143e64a9ac2b6db0ec&imgtype=0&src=http%3A%2F%2Fattimg.dospy.com%2Fimg%2Fday_110703%2F20110703_33257eb2b7f5ecc3c922Wm0c8e98qeWc.jpg',
      'https://timgsa.baidu.com/timg?image&quality=80&size=b9999_10000&sec=1582798380579&di=04e088bedf0eede53eed4cd30e3f9dcf&imgtype=0&src=http%3A%2F%2Fa.hiphotos.baidu.com%2Fzhidao%2Fpic%2Fitem%2F738b4710b912c8fcb3429178fb039245d78821d5.jpg',
       'https://timgsa.baidu.com/timg?image&quality=80&size=b9999_10000&sec=1582798489604&di=9a927b0d8998f9c1964ca659ed61f909&imgtype=0&src=http%3A%2F%2Fattach.bbs.miui.com%2Fforum%2F201501%2F10%2F213416k1aicp2ol12hcmc5.jpg',
    ],
    indicatorDots: true,
    autoplay: true,
    interval: 3000,
    duration: 1000,
    navItems:[
      {
        name:'外卖',
        url:'take'
      },
      {
        name:'餐厅简介',
        url:'dishes',
        isSplot:true
      },
      {
        name:'蓝牙打印',
        url:'bluetooth'
      },
      {
        name:'进货单',
        url:'input'
      },
      {
        name:'库存单',
        url:'bag',
        isSplot:true
      },
      {
        name:'日流水',
        url:'bill'
      }
    ]
  },
  onLoad: function () {
    console.log('onLoad')
  }
    
})
