package Model;

public class AppException extends Exception {

	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	private String text;

	public AppException(String exceptionText) {
		this.text = exceptionText;
	}

	public String getText() {
		return this.text;
	}

}
