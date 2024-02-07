package src;

import java.util.ArrayList;

/**
 * Class Padaria
 */
public class Padaria {

	//
	// Fields
	//

	private Estoque estoquePadaria;
	private double caixa;
	private ArrayList<Funcionarios> funcionarios;

	//
	// Constructors
	//
	public Padaria() {
	};

	//
	// Methods
	//

	//
	// Accessor methods
	//

	/**
	 * Set the value of estoquePadaria
	 * 
	 * @param newVar the new value of estoquePadaria
	 */
	public void setEstoquePadaria(Estoque newVar) {
		estoquePadaria = newVar;
	}

	/**
	 * Get the value of estoquePadaria
	 * 
	 * @return the value of estoquePadaria
	 */
	public Estoque getEstoquePadaria() {
		return estoquePadaria;
	}

	/**
	 * Set the value of caixa
	 * 
	 * @param newVar the new value of caixa
	 */
	public void setCaixa(double newVar) {
		caixa = newVar;
	}

	/**
	 * Get the value of caixa
	 * 
	 * @return the value of caixa
	 */
	public double getCaixa() {
		return caixa;
	}

	/**
	 * Set the value of funcionarios
	 * 
	 * @param newVar the new value of funcionarios
	 */
	public void setFuncionarios(ArrayList<Funcionarios> newVar) {
		funcionarios = newVar;
	}

	/**
	 * Get the value of funcionarios
	 * 
	 * @return the value of funcionarios
	 */
	public ArrayList<Funcionarios> getFuncionarios() {
		return funcionarios;
	}

	public void pagarSalario(Funcionarios funcionario, double valor) {
		if (funcionarios.contains(funcionario)) {
			funcionario.receberSalario(valor); // Adiciona o valor ao salário do funcionário
			caixa -= valor; // Reduz o valor do caixa da padaria
			System.out.println("Salário pago para " + funcionario.getNomeFunc());
			System.out.println("Novo valor no caixa da padaria: " + caixa);
		} else {
			System.out.println("Funcionário não encontrado na lista da padaria.");
		}
	}
	//
	// Other methods
	//

}