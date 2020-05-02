package Lab3InLab;

import domain.Tema;
import org.junit.Test;
import repository.TemaFileRepository;

import static org.junit.Assert.assertTrue;


/**
 * Unit test for simple App.
 */
public class AppTest 
{
    /**
     * Rigorous Test :-)
     */
    @Test
    public void shouldAnswerWithTrue()
    {
        assertTrue( true );
    }


    @Test
    public void testAddAssignment() {
        TemaFileRepository tfr = new TemaFileRepository("fisiere/TemaTest.txt");

        tfr.save(new Tema("100", "cea mai smechera tema", 6, 7));

        assert(tfr.findOne("100").getID().equals("100"));
    }

    @Test
    public void testAddAssignment2() {
        TemaFileRepository tfr = new TemaFileRepository("fisiere/TemaTest.txt");

        assert(tfr.save(new Tema("10", "cea mai smechera tema", 6, 7)) == null);
        assert(tfr.save(new Tema("10", "cea mai smechera tema", 6, 7)) != null);

        assert(tfr.delete("10") != null);
    }
}
