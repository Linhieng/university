import javax.swing.*;
import java.awt.*;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.math.BigDecimal;
import java.math.RoundingMode;
import java.text.DecimalFormat;
import java.util.LinkedList;

public class Main {
    public static void main(String[] args) {
        EventQueue.invokeLater(ComputeFrame::new);
    }
}

class ComputeFrame extends JFrame {

    private static final int MIN_DEFAULT_WIDTH = 400; // 最小宽度
    private static final int MIN_DEFAULT_HEIGHT = 600; // 最小高度

    private final JPanel showPanel = new JPanel(); // 显示屏面板
    private final JPanel buttonPanel = new JPanel(); // 按钮面板
    private final JMenuBar menuBar = new JMenuBar(); // 菜单

    private final JTextArea textArea = new JTextArea(2, 13); // 显示用户用户输入
    private final JTextArea resultArea = new JTextArea(); // 显示运算结果或报错提示

    private String inputTemp = ""; // 存储用户输入的单个数字, 只存数字，不存符号
    private LinkedList<String> input = new LinkedList<>(); // 存储计算列表

    private String preNum = ""; // 幂乘运算符前面的数字的计算结果

    private boolean isComputePower = false; // 是否计算幂乘
    private boolean isCompute = false; // 点击等于号，计算完毕后会变为 true
    private boolean isJustCompute = false; // 是否刚进行快捷运算(除了四则运算外的运算)

    public ComputeFrame() {

        // 窗口居中显示
        var screenSize = Toolkit.getDefaultToolkit().getScreenSize(); // 可获取屏幕宽高
        setLocation(screenSize.width/2-MIN_DEFAULT_WIDTH/2, screenSize.height/2-MIN_DEFAULT_HEIGHT/2); // 设置窗口的左边距和上边距

        setMinimumSize(new Dimension(MIN_DEFAULT_WIDTH, MIN_DEFAULT_HEIGHT)); // 设置最小大小
        setDefaultCloseOperation(EXIT_ON_CLOSE); // 设置关闭方式
        setVisible(true); // 显示

        initMenu(); // 初始化菜单
        initShow(); // 初始化显示区
        initButton(); // 初始化按钮

        setJMenuBar(menuBar); // 添加菜单值窗口
        add(showPanel, BorderLayout.NORTH); // 显示屏在上分
        add(buttonPanel); // 按钮在下方
    }

    /**
     * 添加 help 菜单，点击可查看程序的相关说明
     */
    void initMenu() {

        var editMenu = new JMenu("Help");
        menuBar.add(editMenu);
        editMenu.addMouseListener(new MouseAdapter() { // 为菜单绑定鼠标事件
            @Override // 鼠标点击事件
            public void mouseClicked(MouseEvent e) {
                super.mouseClicked(e);

                // 显示一个对话框
                JOptionPane.showMessageDialog(null,
                        "欢迎使用此计算器！！！" +
                        "\n使用该计算器时，请确保输入的格式正确" +
                        "\n如果输入的格式不正确，将会报错并且无法显示正确答案" +

                        "\n\n使用快捷运算（四则运算外的运算）会直接显示计算在计算列表上" +
                        "\n本计算器中，快捷运算的保留小数最大是9位小数" +
                        "\n而结果显示的小数最大是6位小数" +
                        "\n幂乘运算中，会对幂数进行四舍五入转换为整数！" +
                        "\n计算sin cos 开方时，输入的数字单位是度数！" +

                        "\n\n注意：进行幂乘运算时会在结果区显示计算过程" +
                        "\n计算幂乘运算时如果点击快捷运算，会先继续幂乘运算，再进行快捷运算" +

                        "\n\n点击等于号后，暂时不会清空计算列表，但其实此时计算列表是空的" +
                        "\n所以如果此时直接点击快捷运算，将会提示前面没有数字可以进行运算"
                );
            }
        });

    }

    /**
     * 初始化显示区，共有两个文本区，一个显示计算列表，一个显示答案和报错信息
     */
    void initShow() {

        showPanel.setLayout(new GridLayout(2, 1, 0, 0)); // 两行一列，间距为0

        textArea.setEditable(false); // 不可编辑
        textArea.setFont(new Font("", Font.BOLD, 28)); // 设置字体
        // 可滚动，并且不显示水平滚动条
        var slider1 = new JScrollPane(textArea, ScrollPaneConstants.VERTICAL_SCROLLBAR_NEVER, ScrollPaneConstants.HORIZONTAL_SCROLLBAR_AS_NEEDED);

        resultArea.setEditable(false); // 不可编辑
        resultArea.setFont(new Font("", Font.ITALIC, 28)); // 设置字体
        // 可滚动，并且不显示水平滚动条
        var slider2 = new JScrollPane(resultArea, ScrollPaneConstants.VERTICAL_SCROLLBAR_NEVER, ScrollPaneConstants.HORIZONTAL_SCROLLBAR_AS_NEEDED);

        // 添加至显示面板
        showPanel.add(slider1, BorderLayout.NORTH);
        showPanel.add(slider2, BorderLayout.SOUTH);
    }

    /**
     * 通过调用 makeButton 来初始化按钮
     */
    void initButton() {
        // 设置按钮面板的行列数
        int rows = 7;
        int cols = 4;
        buttonPanel.setLayout(new GridLayout(rows,cols, 4, 4));

        String[] str = { // 按钮内容
                "√", "sin", "cos", "^",
                "!", "1/x", "x^2", "x^3",
                "(", ")", "C", "del",

                "7", "8", "9", "/",
                "4", "5", "6", "*",
                "1", "2", "3", "-",
                "0", ".", "=", "+"
        };

        for (int i = 0; i < rows*cols; i++) {
            makeButton(str[i]); // 创建按钮
        }
    }

    /**
     * 创建按钮组件并添加至按钮面板。
     * 通过调用 addAction 为按钮绑定事件，
     * @param str 按钮上显示的文本信息
     */
    void makeButton(String str) {

        var btn = new JButton(str); // 创建按钮对象

        // 设置按钮上文字样式
        var font = new Font("", Font.BOLD, 32);
        btn.setFont(font);

        buttonPanel.add(btn); // 将按钮添加到面板上显示

        btn.addActionListener(event -> { // 为按钮绑定事件
            addAction(str); // 将数据传递给 calculate 进行计算
        });
    }

    /**
     * 用户点击按钮的回调事件
     * @param str 按钮上显示的值
     */
    void addAction(String str) {

        try {
            System.out.println("点击了"+str+"键，此时 isCompute = " + isCompute + ", isComputePower = "+isComputePower+", isJustCompute = " + isJustCompute);

            if (isCompute) {
                // 清空计算列表
                isCompute = false;
                input = new LinkedList<>();
                textArea.setText("");
            }

            resultArea.setText("");
            resultArea.setForeground(Color.BLACK); // 结果栏显示黑色

            if (str.matches("[0-9.]")) { // 点击数字
                if (isJustCompute) {  // 刚计算完单目运算（除了四则运算外的运算）
                    isJustCompute = false;
                    inputTemp = input.removeLast();
                }
                inputTemp += str; // 拼接数字
            } else {
                // 点击的不是数字，说明数字输入完毕
                if (inputTemp.length() != 0) {
                    input.add(inputTemp);
                    inputTemp = "";
                }

                switch (str) {
                    case "del" :
                        isJustCompute = false;
                        delete();
                        break;

                    case "C" :
                        inputTemp = "";
                        input = new LinkedList<>();
                        resultArea.setText("");
                        isJustCompute = false;
                        isComputePower = false;
                        break;

                    case ")" : case "(" :
                        isJustCompute = false;
                        input.add(str);
                        break;

                    case "+" : case "-" :
                    case "*" : case "/" :
                        isJustCompute = false;
                        computePower(); // 是否要计算幂乘
                        input.add(str);
                        break;

                    case "=" :
                        System.out.println("点击了等于号，开始计算， 要计算的列表为 " + input);
                        computePower(); // 是否要计算幂乘
                        resultArea.setText(new DecimalFormat("0.######").format(Double.parseDouble(calculateRPN(input)))); // 进行四则运算并将结果显示
                        isJustCompute = false;
                        isCompute = true; // 计算完成后开放清空计算列表功能
                        break;

                    //=================进行快捷运算========================

                    case "^" :
                        isJustCompute = false;
                        preNum = new DecimalFormat("0.#########").format(getPreNum()); // 获取符号的前面数字之和
                        input.add(preNum); // 替换掉前面用来计算的列表
                        input.add(str); // 添加 ^ 符号(注意不要提前添加)
                        isComputePower = true; // 标识要计算幂乘
                        break;

                    case "sin":
                        computePower(); // 是否要计算幂乘
                        // 获取符号前面的数字之和，计算其 sin 值，并保留三位小数，然后添加到计算列表中
                        input.add(new DecimalFormat("0.#########").format(Math.sin(Math.toRadians(getPreNum()))));
                        isJustCompute = true;
                        break;

                    case "cos":
                        computePower(); // 是否要计算幂乘
                        // 获取符号前面的数字之和，计算其 cos 值，并保留三位小数，然后添加到计算列表中
                        input.add(new DecimalFormat("0.#########").format(Math.cos(Math.toRadians(getPreNum()))));
                        isJustCompute = true;
                        break;

                    case "√":
                        computePower(); // 是否要计算幂乘
                        // 获取符号前面的数字之和，计算其 开方 值，并保留三位小数，然后添加到计算列表中
                        input.add(new DecimalFormat("0.#########").format(Math.sqrt(getPreNum())));
                        isJustCompute = true;
                        break;

                    case "!":
                        computePower(); // 是否要计算幂乘
                        input.add(factorial(Integer.parseInt(new DecimalFormat("#").format(getPreNum()))));
                        isJustCompute = true;
                        break;

                    case "1/x":
                        computePower(); // 是否要计算幂乘
                        input.add(new DecimalFormat("0.#########").format(Double.parseDouble(calculate(1, getPreNum(), "/"))));
                        isJustCompute = true;
                        break;

                    case "x^2":
                        computePower(); // 是否要计算幂乘
                        input.add(new DecimalFormat("0.#########").format(Double.parseDouble(pow(getPreNum(), 2))));
                        isJustCompute = true;
                        break;

                    case "x^3":
                        computePower(); // 是否要计算幂乘
                        input.add(new DecimalFormat("0.#########").format(Double.parseDouble(pow(getPreNum(), 3))));
                        isJustCompute = true;
                        break;

                }

            }

            // 显示计算列表和结果值
            StringBuilder allInput = new StringBuilder();
            for (String s : input) allInput.append(s);
            textArea.setText(allInput + inputTemp);

        } catch (Exception e) {
            System.err.println("按钮回调函数出错");
            System.err.println(e.getMessage());
            e.printStackTrace();
            resultArea.setForeground(Color.RED);
            resultArea.setText("Syntax ERROR");
        }
    }

    /**
     * 判断是否要计算幂乘，若需要，则直接进行计算
     * @throws Exception 抛出 getPreNum 的异常信息
     */
    void computePower() throws Exception{

        if (isComputePower) {

            isComputePower = false;

            // ^ 符号前面的数字之和
            String nextNum = new DecimalFormat("#").format(getPreNum());
            double pre = Double.parseDouble(preNum);
            int next = Integer.parseInt(nextNum);
            input.removeLast(); // 删除 ^ 符号
            String temp = input.removeLast(); // 获取并删除 ^符号前面的数字
            if (temp.matches("-?\\d+(\\.\\d+)?]"))
                throw new Exception("^ 前面的值不是一个数字？？？值为" + temp); // 删除 ^ 符号前面的数字
            var result = pow(pre, next);
            input.add(result);
            resultArea.setText("" + pre + "^" + next + "=" + result);
        }
    }

    /**
     * 计算幂乘 pre ^ next
     * @param pre 底数，可以为 double 类型
     * @param next 几次幂，只允许整数
     * @return 结果值
     */
    String pow(double pre, int next) {
        int power = Math.abs(next);
        BigDecimal num = new BigDecimal(pre);
        BigDecimal result = num;

        while (power > 1) {
            result = result.multiply(num);
            power--;
        }

        if (next > 0)
            return String.valueOf(result);
        return new DecimalFormat("0.#########").format(1 / Double.parseDouble(String.valueOf(result)));
    }

    /**
     * 先删除 inputTemp 的最后一个字符
     * inputTemp 为空，则从 input 中取出一个作为  inputTemp
     * 然后继续删除 inputTemp 的最后一个字符
     */
    void delete() {
        int length = inputTemp.length();
        if (length > 0)
            inputTemp = inputTemp.substring(0, length - 1); // 删除字符串最后一个字符
        else if (!input.isEmpty()) {
                // 取出最后一个字符并进行删除
            inputTemp = input.removeLast();
            inputTemp = inputTemp.substring(0, inputTemp.length() - 1);
        }
    }

    /**
     * 计算运算符前面的数字之和
     * 会在 input 中删除掉用来计算的数字
     * @return 计算值
     * @throws Exception 可能出现的未知异常 和 括号无法匹配成功
     */
    double getPreNum(/*LinkedList<String> input*/) throws Exception{
        // 先获取前面的数字的计算列表

        var stackTemp = new LinkedList<String>(); // 模拟栈结果
        int bracketNum = 0; // 待匹配的括号数量

        if (input.isEmpty())
            throw new Exception("运算符前面没有数字可以进行运算");

        if (")".equals(input.getLast())) {
            // 括号、数字、运算符全部都要添加进去
            bracketNum++;
            stackTemp.addFirst(input.removeLast());

            // 直到匹配到对应的左括号
            while (bracketNum != 0) {
                if (input.isEmpty())
                    throw new Exception("为空了还没有找齐左括号，说明格式错误， 已遍历到的内容为：" + stackTemp);
                String temp = input.removeLast(); // 取出最后一个
                stackTemp.addFirst(temp); // 添加到开头
                if (")".equals(temp)) bracketNum++;
                if ("(".equals(temp)) bracketNum--;
            }

        } else if (input.getLast().matches("-?\\d+(\\.\\d+)?")) {
            // 为数字，直接添加
            stackTemp.add(input.removeLast());

        } else {
            throw new Exception("运算符前面一位不是右括号也不是数字，说明输入格式错误，前面一位内容为： " + input.getLast());
        }

        System.out.println("获取到的运算符前面的数字计算列表为： " + stackTemp);

        // 将列表地址引用过去进行计算，并将值返回
        return Double.parseDouble(calculateRPN(stackTemp));
    }

    /**
     * RPN 逆波兰法计算四则运算
     * @param input 接收一个链表地址引用, 注意没有进行克隆
     * @return 计算结果
     */
    String calculateRPN(LinkedList<String> input) throws Exception {

        // 中缀表达式转换为后缀表达式

        var suffix = new LinkedList<String>(); // 存储后缀表达式
        var stackTemp = new LinkedList<String>(); // 模拟栈结构
        for (String s : input) { // 依次遍历计算列表

            if (s.matches("-?\\d+(\\.\\d+)?")) {
                // 数字直接输出到后缀表达式
                suffix.add(s);
            }
            else if (s.matches("[-+*/)(]")) {

                // 栈为空，直接添加符号。
                if (stackTemp.isEmpty()) {
                    stackTemp.add(s);
                }
                else if ("(".equals(s)) { // 左括号直接入栈
                    stackTemp.add(s);
                }
                else if (")".equals(s)) {
                    // 遇到右括号，则匹配第一个左括号(因为不可能出现两个右括号)
                    while (!"(".equals(stackTemp.getLast())) {
                        suffix.add(stackTemp.removeLast());

                        if (stackTemp.isEmpty())
                            throw new Exception("转换为后缀表达式过程中，栈都空了，还找不到左括号， 输出已添加的后缀表达式：" + suffix);
                    }
                    stackTemp.removeLast(); // 匹配到左括号了，故删去左括号

                }
                else { // 四则运算符肯定是先入栈的，但在入栈之前要先判断是否要将栈顶元素输出

                    // 优先级不高于栈顶元素(栈顶元素不是左括号的前提下)，则弹出栈顶元素
                    while (!"(".equals(stackTemp.getLast()) && isLow(s, stackTemp.getLast())) { // 注意顺序顺序，不然左括号可能进入 isLow
                        suffix.add(stackTemp.removeLast());
                        if (stackTemp.isEmpty()) break;
                    }
                    stackTemp.add(s); // 运算符入栈
                }
            }
            else {
                throw new Exception("转换为后缀表达式时出错(重复验证)不是数字也不是指定的运算符，说明格式错误, 值为：" + s + ", 剩余的 input = " + input);
            }

        }

        // 将剩余的运算符全部弹栈
        while (!stackTemp.isEmpty()) {
            String temp = stackTemp.removeLast();
            if (temp.matches("[-+*/]"))
                suffix.add(temp);

        }
        System.out.println("计算出的后缀表达式" + suffix);

        // 对后缀表达式进行运算

        for (String s : suffix) {
            if (s.matches("-?\\d+(\\.\\d+)?")) {
                stackTemp.add(s); // 数字直接入栈，等待计算
            }
            else if (s.matches("[-+*/]")){
                // 只允许四种符号

                if (stackTemp.size() < 2)
                    throw new Exception("计算出的后缀表达式有问题， stackTemp 没有足够的数字进行运算, stackTemp = " + stackTemp);

                double a = Double.parseDouble(stackTemp.removeLast());
                double b = Double.parseDouble(stackTemp.removeLast()); // 取出两个栈顶元素
                stackTemp.add(calculate(b, a, s)); // 使用 大数 进行运算
            } else {
                // 多次验证
                throw new Exception("对后缀表达式进行运算时，遇到不为数字也不为-+*/符号的字符串， 该字符串为 ：" + s);
            }
        }

        return stackTemp.getLast(); // 返回计算结果
    }

    /**
     * 判断 temp 运算符的优先级是否比 top 的优先级低(包括相等)
     * @param temp 待比较的运算符
     * @param top 栈顶运算符
     * @return true 代表 temp 运算符不高于 top
     */
    boolean isLow(String temp, String top) throws Exception {
        if (!temp.matches("[-+*/]")) throw new Exception("该方法只能比较四种符号的优先级 temp 符号错误， temp = " + temp);
        if (!top.matches("[-+*/]")) throw new Exception("该方法只能比较四种符号的优先级 top 符号错误， top = " + top);

        int a = temp.matches("[-+]")? 0 : 1;
        int b = top.matches("[-+]")? 0 : 1;
        return a <= b;
    }

    /**
     * 使用大数计算 a · b
     * @param a 计算的数字
     * @param b 计算的数字
     * @param operator 运算符，+ - * /
     * @return 计算结果
     */
    String calculate(double a, double b, String operator) throws Exception {

        BigDecimal aB = BigDecimal.valueOf(a);
        BigDecimal bB = BigDecimal.valueOf(b);

        System.out.println("大数运算 " + aB + operator + bB);

        if ("+".equals(operator))
            return String.valueOf(aB.add(bB));
        if ("-".equals(operator))
            return String.valueOf(aB.subtract(bB));
        if ("*".equals(operator))
            return String.valueOf(aB.multiply(bB));
        if ("/".equals(operator)) {

            aB = aB.multiply(new BigDecimal("1.000000000000000000000")); // 确保精度，注意得使用字符串创建才有效
            System.out.println(aB);
            return String.valueOf(aB.divide(bB, RoundingMode.HALF_UP)); // 四舍五入
        }
        throw new Exception("进行大数运算时，传入的运算符出现错误，该运算符为 " + operator);
    }

    /**
     * 计算阶乘，为保证精度，使用大数进行计算
     * @param x 要计算的数字
     * @return 计算结果
     */
    String factorial(int x) {

        // 不使用递归
        String symbol = "";
        int i = 1;
        BigDecimal num = new BigDecimal("1");

        if (x < 0) {
            symbol = "-";
            x = -x;
        }

        while (x-- > 1) { // 1*2*3...
            num = num.multiply(BigDecimal.valueOf(++i));
        }

        return symbol + num;
    }
}