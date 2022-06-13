
namespace MazeChallenge
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle1 = new System.Windows.Forms.DataGridViewCellStyle();
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.fileToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.openMazeToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.exitToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.helpToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.aboutToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.solveToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.strategiesToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.depthFirstSearchToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.nonGreedyAToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.mazeBlocksDataGrid = new System.Windows.Forms.DataGridView();
            this.openMazeFileDialog = new System.Windows.Forms.OpenFileDialog();
            this.menuStrip1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.mazeBlocksDataGrid)).BeginInit();
            this.SuspendLayout();
            // 
            // menuStrip1
            // 
            this.menuStrip1.ImageScalingSize = new System.Drawing.Size(20, 20);
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fileToolStripMenuItem,
            this.helpToolStripMenuItem,
            this.solveToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(617, 28);
            this.menuStrip1.TabIndex = 0;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // fileToolStripMenuItem
            // 
            this.fileToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.openMazeToolStripMenuItem,
            this.exitToolStripMenuItem});
            this.fileToolStripMenuItem.Name = "fileToolStripMenuItem";
            this.fileToolStripMenuItem.Size = new System.Drawing.Size(46, 24);
            this.fileToolStripMenuItem.Text = "File";
            // 
            // openMazeToolStripMenuItem
            // 
            this.openMazeToolStripMenuItem.Name = "openMazeToolStripMenuItem";
            this.openMazeToolStripMenuItem.Size = new System.Drawing.Size(168, 26);
            this.openMazeToolStripMenuItem.Text = "Open Maze";
            this.openMazeToolStripMenuItem.Click += new System.EventHandler(this.openMazeToolStripMenuItem_Click);
            // 
            // exitToolStripMenuItem
            // 
            this.exitToolStripMenuItem.Name = "exitToolStripMenuItem";
            this.exitToolStripMenuItem.Size = new System.Drawing.Size(168, 26);
            this.exitToolStripMenuItem.Text = "Exit";
            this.exitToolStripMenuItem.Click += new System.EventHandler(this.exitToolStripMenuItem_Click);
            // 
            // helpToolStripMenuItem
            // 
            this.helpToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.aboutToolStripMenuItem});
            this.helpToolStripMenuItem.Name = "helpToolStripMenuItem";
            this.helpToolStripMenuItem.Size = new System.Drawing.Size(55, 24);
            this.helpToolStripMenuItem.Text = "Help";
            // 
            // aboutToolStripMenuItem
            // 
            this.aboutToolStripMenuItem.Name = "aboutToolStripMenuItem";
            this.aboutToolStripMenuItem.Size = new System.Drawing.Size(133, 26);
            this.aboutToolStripMenuItem.Text = "About";
            this.aboutToolStripMenuItem.Click += new System.EventHandler(this.aboutToolStripMenuItem_Click);
            // 
            // solveToolStripMenuItem
            // 
            this.solveToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.strategiesToolStripMenuItem});
            this.solveToolStripMenuItem.Name = "solveToolStripMenuItem";
            this.solveToolStripMenuItem.Size = new System.Drawing.Size(59, 24);
            this.solveToolStripMenuItem.Text = "Solve";
            // 
            // strategiesToolStripMenuItem
            // 
            this.strategiesToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.depthFirstSearchToolStripMenuItem,
            this.nonGreedyAToolStripMenuItem});
            this.strategiesToolStripMenuItem.Name = "strategiesToolStripMenuItem";
            this.strategiesToolStripMenuItem.Size = new System.Drawing.Size(158, 26);
            this.strategiesToolStripMenuItem.Text = "Strategies";
            // 
            // depthFirstSearchToolStripMenuItem
            // 
            this.depthFirstSearchToolStripMenuItem.Name = "depthFirstSearchToolStripMenuItem";
            this.depthFirstSearchToolStripMenuItem.Size = new System.Drawing.Size(212, 26);
            this.depthFirstSearchToolStripMenuItem.Text = "Depth First Search";
            this.depthFirstSearchToolStripMenuItem.Click += new System.EventHandler(this.depthFirstSearchToolStripMenuItem_Click);
            // 
            // nonGreedyAToolStripMenuItem
            // 
            this.nonGreedyAToolStripMenuItem.Name = "nonGreedyAToolStripMenuItem";
            this.nonGreedyAToolStripMenuItem.Size = new System.Drawing.Size(212, 26);
            this.nonGreedyAToolStripMenuItem.Text = "Non Greedy A*";
            this.nonGreedyAToolStripMenuItem.Click += new System.EventHandler(this.nonGreedyAToolStripMenuItem_Click);
            // 
            // mazeBlocksDataGrid
            // 
            this.mazeBlocksDataGrid.AllowUserToAddRows = false;
            this.mazeBlocksDataGrid.AllowUserToDeleteRows = false;
            this.mazeBlocksDataGrid.AllowUserToResizeColumns = false;
            this.mazeBlocksDataGrid.AllowUserToResizeRows = false;
            this.mazeBlocksDataGrid.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.mazeBlocksDataGrid.ColumnHeadersVisible = false;
            dataGridViewCellStyle1.Alignment = System.Windows.Forms.DataGridViewContentAlignment.MiddleCenter;
            dataGridViewCellStyle1.BackColor = System.Drawing.SystemColors.Window;
            dataGridViewCellStyle1.Font = new System.Drawing.Font("Microsoft Sans Serif", 7.8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            dataGridViewCellStyle1.ForeColor = System.Drawing.SystemColors.HotTrack;
            dataGridViewCellStyle1.Padding = new System.Windows.Forms.Padding(1);
            dataGridViewCellStyle1.SelectionBackColor = System.Drawing.SystemColors.GradientActiveCaption;
            dataGridViewCellStyle1.SelectionForeColor = System.Drawing.SystemColors.ControlText;
            dataGridViewCellStyle1.WrapMode = System.Windows.Forms.DataGridViewTriState.False;
            this.mazeBlocksDataGrid.DefaultCellStyle = dataGridViewCellStyle1;
            this.mazeBlocksDataGrid.Dock = System.Windows.Forms.DockStyle.Fill;
            this.mazeBlocksDataGrid.Location = new System.Drawing.Point(0, 28);
            this.mazeBlocksDataGrid.Name = "mazeBlocksDataGrid";
            this.mazeBlocksDataGrid.RowHeadersVisible = false;
            this.mazeBlocksDataGrid.RowHeadersWidth = 51;
            this.mazeBlocksDataGrid.RowTemplate.Height = 24;
            this.mazeBlocksDataGrid.ScrollBars = System.Windows.Forms.ScrollBars.None;
            this.mazeBlocksDataGrid.Size = new System.Drawing.Size(617, 305);
            this.mazeBlocksDataGrid.TabIndex = 1;
            this.mazeBlocksDataGrid.CellClick += new System.Windows.Forms.DataGridViewCellEventHandler(this.mazeBlocksDataGrid_CellClick);
            // 
            // openMazeFileDialog
            // 
            this.openMazeFileDialog.DefaultExt = "\"txt\"";
            this.openMazeFileDialog.Filter = "txt files (*.txt)|*.txt|All files (*.*)|*.*";
            this.openMazeFileDialog.Title = "Open Maze File";
            this.openMazeFileDialog.FileOk += new System.ComponentModel.CancelEventHandler(this.openMazeFileDialog_FileOk);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(617, 333);
            this.Controls.Add(this.mazeBlocksDataGrid);
            this.Controls.Add(this.menuStrip1);
            this.ForeColor = System.Drawing.SystemColors.HotTrack;
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.MainMenuStrip = this.menuStrip1;
            this.MinimizeBox = false;
            this.Name = "Form1";
            this.ShowIcon = false;
            this.Text = "Maze";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.mazeBlocksDataGrid)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem fileToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem openMazeToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem exitToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem helpToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem aboutToolStripMenuItem;
        private System.Windows.Forms.DataGridView mazeBlocksDataGrid;
        private System.Windows.Forms.ToolStripMenuItem solveToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem strategiesToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem depthFirstSearchToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem nonGreedyAToolStripMenuItem;
        private System.Windows.Forms.OpenFileDialog openMazeFileDialog;
    }
}

