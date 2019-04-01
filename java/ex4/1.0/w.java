（1）实体类FiveChess

public class FiveChess {

    /**

     * 维度

     */

    private int n;

    private double width;

    private double height;

    private double cellLen;

    

    private char[][] chess;



    private char currentSide='B';

   //其他请补充

   

public void play(int x,int y){

     //将当前的棋子放置到（x,y） 

    }



    public void  changeSide(){

     //更换下棋方

        setCurrentSide(currentSide=='B'?'W':'B');

    }

   

public boolean judgeGame(int row, int col, char chessColor){

         //判断游戏是否结束

        

    }

}

（2）视图类ChessPane

  Canvas canvas = new Canvas(800,600);

  GraphicsContext gc = canvas.getGraphicsContext2D();

  gc.strokeRect(leftX,leftY,width,height):从左上角(leftX,leftY)绘制widthXheight的矩形轮廓

  gc.fillRect(leftX,leftY,width,height)：从左上角(leftX,leftY)绘制widthXheight的填充矩形

  gc.strokeOval(leftX,leftY,width,height)：从左上角(leftX,leftY)绘制widthXheight的椭圆形轮廓

  gc.fillOval(leftX,leftY,width,height)：从左上角(leftX,leftY)绘制widthXheight的填充椭圆形

（3）事件处理：

package cn.edu.ncu.chenyi.fivechess.controller;



import cn.edu.ncu.chenyi.fivechess.entity.FiveChess;

import cn.edu.ncu.chenyi.fivechess.view.ChessPane;

import javafx.event.EventHandler;

import javafx.scene.control.Alert;

import javafx.scene.input.MouseEvent;



/**

 * PlayAction.java

 * Copyright: Nanchang University Information School Chen Yi

 *

 * @author 陈轶

 * Created on  2019-03-22 15:16

 * Description:

 **/

public class PlayAction implements EventHandler<MouseEvent> {

     /**fiveChess表示五子棋游戏模型*/

    private FiveChess fiveChess;

    /**chessPane表示五子棋显示面板*/

    private ChessPane chessPane;



    public PlayAction(FiveChess fiveChess,ChessPane chessPane){

        this.chessPane= chessPane;

        this.fiveChess = fiveChess;

    }

    @Override

    public void handle(MouseEvent event) {

        //处理鼠标点击事件

        

      //event.getX()获取鼠标点击x坐标，返回double类型
    }

}


